/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:21:41 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/05 11:37:03 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>

void	make_semaphores(t_data_bonus *data)
{
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("dead");
	sem_unlink("end");
	sem_unlink("eat");
	data->forks = sem_open("forks", O_CREAT, 0666, data->nb_philo);
	data->print = sem_open("print", O_CREAT, 0666, 1);
	data->go_on = sem_open("dead", O_CREAT, 0666, 1);
	data->end = sem_open("end", O_CREAT, 0666, 0);
	data->fed = sem_open("eat", O_CREAT, 0666, 0);
	data->p_eaten = sem_open("p_eaten", O_CREAT, 0666, 0);
}
