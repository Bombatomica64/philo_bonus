/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_process_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:11:54 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/05 11:47:56 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*stop(void *arg)
{
	t_data_bonus	*data;

	data = (t_data_bonus *)arg;
	sem_wait(data->p_eaten);
	data->dead = TRUE;
	return (NULL);
}

void	*philo_eaten(void *arg)
{
	t_data_bonus	*data;
	int				i;

	data = (t_data_bonus *)arg;
	i = 0;
	while (i < data->nb_philo)
	{
		sem_wait(data->fed);
		i++;
		if (i == data->nb_philo)
		{
			if (data->dead == FALSE)
				print_bonus(data, FED, 0, ft_get_time_bonus(&data->time, data));
			break ;
		}
	}
	sem_post(data->end);
	return (NULL);
}
