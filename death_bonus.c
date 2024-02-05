/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:48:57 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/05 11:18:05 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_close_bonus(t_data_bonus *data)
{
	sem_close(data->forks);
	sem_close(data->end);
	sem_close(data->print);
	sem_close(data->go_on);
	// sem_unlink("forks");
	// sem_unlink("print");
	// sem_unlink("dead");
	// sem_unlink("eat");
	// sem_unlink("end");
	free(data->philo);
	free(data);
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
			printf("philo %d ha postato end\n", data->id);
			sem_post(data->data->end);
			post_food(data->data);
			return (NULL);
		}
	}
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
	printf("philo %d is waiting for death\n", data->id);
	sem_wait(data->data->end);
	printf("philo %d terminated\n", data->id);
	go_on_bonus(data->data, TRUE);
/* 	if (data->data->dead_nbr != -1)
		sem_post(data->data->end); */
	return (NULL);
}
