/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:27:41 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/02 16:29:35 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_sleep_think(t_data_bonus *data, int id)
{
	print_bonus(data, SLEEP, id, ft_get_time_bonus(&data->time));
	ft_msleep_bonus(data->time_to_sleep);
	print_bonus(data, THINK, id, ft_get_time_bonus(&data->time));
}

void	philo_eat(t_data_bonus *data, int id)
{
	take_fork(data, id);
	take_fork(data, id);
	print_bonus(data, EAT, id, ft_get_time_bonus(&data->time));
	data->philo[id].nb_meals--;
	get_start_bonus(&data->philo[id].life_left);
	ft_msleep_bonus(data->time_to_eat);
	leave_fork(data, id);
	leave_fork(data, id);
}

void	leave_fork(t_data_bonus *data, int id)
{
	(void)id;
	sem_post(data->forks);
}

void	take_fork(t_data_bonus *data, int id)
{
	sem_wait(data->forks);
	print_bonus(data, FORK, id, ft_get_time_bonus(&data->time));
}

void	philo_life(t_data_bonus *data, int id)
{
	pthread_create(&data->philo[id].thread, NULL,
		&check_death, make_data_id_bonus(data, id));
	pthread_create(&data->philo[id].end, NULL,
		&check_end, make_data_id_bonus(data, id));
	get_start_bonus(&data->philo[id].life_left);
	while (go_on_bonus(data, FALSE) == TRUE)
	{
		philo_eat(data, id);
		philo_sleep_think(data, id);
		printf("[id = %i]go_on_bonus(data, FALSE) = %d\n", id, go_on_bonus(data, FALSE));
	}
	pthread_join(data->philo[id].thread, NULL);
	pthread_join(data->philo[id].end, NULL);
	pthread_detach(data->philo[id].end);
	pthread_detach(data->philo[id].thread);
	ft_close_bonus(data);
}
