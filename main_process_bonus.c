/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_process_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:11:54 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/02 18:46:13 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*philo_eaten(void *arg)
{
	t_data_bonus *data;
	
	data = (t_data_bonus *)arg;
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		sem_wait(data->fed);
		i++;
		if (i == data->nb_philo)
		{
			printf("\n\n\nphilo %d has eaten\n\n\n", i);
			kill(0, SIGINT);
			break;
		}
		
	}
	sem_post(data->end);

	return (NULL);
}
