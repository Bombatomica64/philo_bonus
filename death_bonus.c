/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:48:57 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/05 16:10:34 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_close_bonus(t_data_bonus *data)
{
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->go_on);
	sem_close(data->end);
	sem_close(data->fed);
	sem_close(data->time_lock);
	sem_close(data->p_eaten);
	sem_close(data->start_lock);
	free(data->philo);
	free(data);
	exit(EXIT_SUCCESS);
}

void	*check_death(void *arg)
{
	t_id	*data;

	data = (t_id *)arg;
	while (go_on_bonus(data->data, FALSE) == TRUE)
	{
		data->data->philo[data->id]
			.life_left.time_since = ft_get_time_bonus(&data->data
				->philo[data->id].life_left, data->data);
		if (data->data->philo[data->id]
			.life_left.time_since > data->data->time_to_die)
		{
			data->data->dead_nbr = data->id;
			print_bonus(data->data, DIED, data->id,
				ft_get_time_bonus(&data->data->time, data->data));
			sem_post(data->data->end);
			sem_post(data->data->p_eaten);
			post_food(data->data);
			go_on_bonus(data->data, TRUE);
			free(data);
			return (NULL);
		}
	}
	free(data);
	return (NULL);
}

void	post_food(t_data_bonus *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		sem_post(data->fed);
		i++;
	}
}

void	*check_end(void *arg)
{
	t_id	*data;

	data = (t_id *)arg;
	sem_wait(data->data->end);
	go_on_bonus(data->data, TRUE);
	sem_post(data->data->end);
	free(data);
	return (NULL);
}
