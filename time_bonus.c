/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:46:21 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/05 15:33:18 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	ft_current_time_bonus(void)
{
	struct timeval	tv;
	long long		time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return (time_in_ms);
}

void	ft_msleep_bonus(int time)
{
	long long	tmp;

	tmp = ft_current_time_bonus() + time;
	while (ft_current_time_bonus() < tmp)
		usleep(10);
}

void	get_start_bonus(t_time *start, sem_t *start_lock)
{
	sem_wait(start_lock);
	gettimeofday(&start->start, NULL);
	start->start_ms = (start->start.tv_sec) * 1000
		+ (start->start.tv_usec) / 1000;
	sem_post(start_lock);
}

long long	ft_get_time_bonus(t_time *start, t_data_bonus *data)
{
	long long			time_since;

	time_since = 0;
	sem_wait(data->start_lock);
	sem_wait(data->time_lock);
	time_since = (ft_current_time_bonus() - start->start_ms);
	sem_post(data->time_lock);
	sem_post(data->start_lock);
	return (time_since);
}
