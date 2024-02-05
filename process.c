/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:12:25 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/05 12:49:26 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_for_death(t_data_bonus *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->nb_philo)
	{
		printf("waiting for %d\n", i);
		waitpid(data->philo[i].pid, &status, 0);
		printf("philo %d terminated\n", i);
		i++;
	}
}

void	make_processes(t_data_bonus *data)
{
	int	i;

	i = 0;
	get_start_bonus(&data->time, data->start_lock);
	while (i < data->nb_philo)
	{
		data->philo[i].id = i;
		data->philo[i].nb_meals = data->nb_meals;
		data->go_on_b = TRUE;
		data->philo[i].pid = fork();
		if (data->philo[i].pid == 0)
			philo_life(data, i);
		i++;
	}
	pthread_create(&data->stop_write, NULL, &stop, data);
	pthread_create(&data->eaten, NULL, &philo_eaten, data);
	pthread_detach(data->stop_write);
	pthread_detach(data->eaten);
	wait_for_death(data);
	//close_main(data);
}
