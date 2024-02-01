/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:27:41 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/01 15:59:41 by lmicheli         ###   ########.fr       */
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

t_data_id_bonus	*make_data_id(t_data_bonus *data, int id)
{
	t_data_id_bonus	*data_id;

	data_id = malloc(sizeof(t_data_id_bonus));
	data_id->data = data;
	data_id->id = id;
	return (data_id);
}

void	philo_life(t_data_bonus *data, int id)
{
	pthread_create(&data->philo[id].thread, NULL,
		&check_death, make_data_id(data, id));
	get_start_bonus(&data->philo[id].life_left);
	while (data->philo[id].go_on)
	{
		philo_eat(data, id);
		philo_sleep_think(data, id);
	}
	pthread_join(data->philo[id].thread, NULL);
}
