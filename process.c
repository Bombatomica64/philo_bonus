/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:12:25 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/02 17:18:30 by lmicheli         ###   ########.fr       */
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
		data->go_on_b = TRUE;
		data->philo[i].pid = fork();
		if (data->philo[i].pid == 0)
			philo_life(data, i);
		i++;
	}
	wait_for_death(data);
	exit(EXIT_SUCCESS);
}
