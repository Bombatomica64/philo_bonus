/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:48:57 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/01 18:27:22 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_close_bonus(t_data_bonus *data)
{
	sem_close(data->forks);
//	free(data->forks);
	sem_close(data->end);
//	free(data->end);
	sem_close(data->print);
//	free(data->print);
	sem_close(data->go_on);
//	free(data->go_on);
	free(data->philo);
	free(data);
	exit(EXIT_SUCCESS);
}

t_bool	go_on_bonus(t_data_bonus *data, t_bool stop)
{
	sem_wait(data->go_on);
	if (stop == TRUE)
	{
		sem_post(data->go_on);
		return (FALSE);
	}
	else
	{
		sem_post(data->go_on);
		return (TRUE);
	}
}

void	*check_death(void *arg)
{
	t_id	*data;

	data = (t_id *)arg;
	while (TRUE)
	{
		data->data->philo[data->id]
			.life_left.time_since = ft_get_time_bonus(&data->data->time);
		if (data->data->philo[data->id]
			.life_left.time_since > data->data->time_to_die)
		{
			data->data->philo[data->id].go_on = FALSE;
			print_bonus(data->data, DIED, data->id,
				ft_get_time_bonus(&data->data->time));
			sem_post(data->data->end);
			return (NULL);
		}
		if (sem_wait(data->data->end) != -1)
		{
			sem_post(data->data->end);
			data->data->philo[data->id].go_on = FALSE;
			return (NULL);
		}
	}
	return (NULL);
}
