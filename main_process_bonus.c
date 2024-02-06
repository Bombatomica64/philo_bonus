/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_process_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:11:54 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/06 16:05:00 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*stop(void *arg)
{
	t_data_bonus	*data;

	data = (t_data_bonus *)arg;
	sem_wait(data->p_eaten);
	if (data->nb_philo == 1)
		sem_wait(data->fed);
	data->dead = TRUE;
	if (data->nb_philo == 1)
		sem_post(data->fed);
	sem_close(data->p_eaten);
	sem_unlink("p_eaten");
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
			{
				sem_post(data->p_eaten);
				sem_post(data->end);
				print_bonus(data, FED, 0, ft_get_time_bonus(&data->time, data));
			}
			break ;
		}
	}
	sem_post(data->end);
	return (NULL);
}

void	close_main(t_data_bonus *data)
{
	post_food(data);
	sem_post(data->end);
	sem_post(data->print);
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->go_on);
	sem_close(data->end);
	sem_close(data->fed);
	sem_close(data->time_lock);
	sem_close(data->start_lock);
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("dead");
	sem_unlink("end");
	sem_unlink("eat");
	sem_unlink("time_lock");
	sem_unlink("start_lock");
	free(data->philo);
	free(data);
}
