/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:27:41 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/05 16:38:54 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_sleep_think(t_data_bonus *data, int id)
{
	print_bonus(data, SLEEP, id, ft_get_time_bonus(&data->time, data));
	ft_msleep_bonus(data->time_to_sleep);
	print_bonus(data, THINK, id, ft_get_time_bonus(&data->time, data));
}

void	philo_eat(t_data_bonus *data, int id)
{
	take_fork(data, id);
	take_fork(data, id);
	print_bonus(data, EAT, id, ft_get_time_bonus(&data->time, data));
	data->philo[id].nb_meals--;
	get_start_bonus(&data->philo[id].life_left, data->start_lock);
	ft_msleep_bonus(data->time_to_eat);
	if (data->philo[id].nb_meals == 0)
		sem_post(data->fed);
	leave_fork(data, id);
	leave_fork(data, id);
}

void	leave_fork(t_data_bonus *data, int id)
{
	(void)id;
	sem_post(data->forks);
}

void	take_fork(t_data_bonus *data, int id)
{
	sem_wait(data->forks);
	print_bonus(data, FORK, id, ft_get_time_bonus(&data->time, data));
}

void	philo_life(t_data_bonus *data, int id)
{
	if (data->nb_philo == 1)
	{
		alone(data, id);
		ft_close_bonus(data);
	}
	pthread_create(&data->philo[id].thread, NULL,
		&check_death, make_data_id_bonus(data, id));
	pthread_create(&data->philo[id].end, NULL,
		&check_end, make_data_id_bonus(data, id));
	if (id % 2 == 0)
		ft_msleep_bonus(100);
	while (go_on_bonus(data, FALSE) == TRUE)
	{
		philo_eat(data, id);
		philo_sleep_think(data, id);
	}
	pthread_join(data->philo[id].thread, NULL);
	pthread_join(data->philo[id].end, NULL);
	pthread_detach(data->philo[id].end);
	pthread_detach(data->philo[id].thread);
	ft_close_bonus(data);
}
