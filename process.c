/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:12:25 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/02 15:11:50 by mruggier         ###   ########.fr       */
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
		waitpid(data->philo[i].pid, &status, 0);
		printf("philo %d terminated\n", i);
		i++;
	}
}

void	make_processes(t_data_bonus *data)
{
	int	i;

	i = 0;
	get_start_bonus(&data->time);
	while (i < data->nb_philo)
	{
		data->philo[i].id = i;
		data->philo[i].nb_meals = data->nb_meals;
		data->philo[i].go_on = TRUE;
		data->philo[i].pid = fork();
		if (data->philo[i].pid == 0)
			philo_life(data, i);
		i++;
	}
	wait_for_death(data);
	exit(EXIT_SUCCESS);
}
