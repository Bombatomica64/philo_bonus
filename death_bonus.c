/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:48:57 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/02 18:26:31 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_close_bonus(t_data_bonus *data)
{
	(void)data;
	sem_close(data->forks);
	//free(data->forks);
	sem_close(data->end);
	//free(data->end);
	sem_close(data->print);
	//free(data->print);
	sem_close(data->go_on);
	//free(data->go_on);
	
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("dead");
	sem_unlink("eat");
	sem_unlink("end");
	
	free(data->philo);
	free(data);
	// kill(0, SIGTERM);
	printf("philo terminated\n");
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
			->philo[data->id].life_left);
		if (data->data->philo[data->id]
			.life_left.time_since > data->data->time_to_die)
		{
			data->data->dead_nbr = data->id;
			go_on_bonus(data->data, TRUE);
			print_bonus(data->data, DIED, data->id,
				ft_get_time_bonus(&data->data->time));
			sem_post(data->data->end);
			return (NULL);
		}
/* 		if (sem_wait(data->data->end) != -1)
		{
			sem_post(data->data->end);
			go_on_bonus(data->data, TRUE);
			return (NULL);
		} */
	}
	return (NULL);
}

void	*check_end(void *arg)
{
	t_id	*data;

	data = (t_id *)arg;
	printf("philo %d is waiting for death\n", data->id);
	sem_wait(data->data->end);
	printf("philo %d terminated\n", data->id);
	go_on_bonus(data->data, TRUE);
/* 	if (data->data->dead_nbr != -1)
		sem_post(data->data->end); */
	return (NULL);
}