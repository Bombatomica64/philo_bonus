/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:21:41 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/06 12:17:45 by lmicheli         ###   ########.fr       */
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
	sem_unlink("time_lock");
	sem_unlink("p_eaten");
	sem_unlink("start_lock");
	data->forks = sem_open("forks", O_CREAT, 0666, data->nb_philo);
	data->print = sem_open("print", O_CREAT, 0666, 1);
	data->go_on = sem_open("dead", O_CREAT, 0666, 1);
	data->end = sem_open("end", O_CREAT, 0666, 0);
	data->fed = sem_open("eat", O_CREAT, 0666, 0);
	data->time_lock = sem_open("time_lock", O_CREAT, 0666, 1);
	data->p_eaten = sem_open("p_eaten", O_CREAT, 0666, 0);
	data->start_lock = sem_open("start_lock", O_CREAT, 0666, 1);
	get_start_bonus(&data->time, data->start_lock);
}
