/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:19:27 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/02 16:30:00 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_bonus(t_data_bonus *data, t_action action, int id, long time_s)
{
	sem_wait(data->print);
	if (go_on_bonus(data, FALSE) == FALSE && action != DIED)
	{
		sem_post(data->print);
		return ;
	}
	prints_b(action, time_s, id, data);
	sem_post(data->print);
}

void	prints_b(t_action action, long time_since, int id, t_data_bonus *data)
{
	if (action == EAT)
		printf("\033[1m%ld\033[0;91m philo[%d] is eating\033[0m 🍝️\n",
			time_since, id +1);
	else if (action == SLEEP)
		printf("\033[1m%ld \033[0;34mphilo[%d] is sleeping\033[0m 💤️\n",
			time_since, id +1);
	else if (action == THINK)
		printf("\033[1m%ld \033[0;36mphilo[%d] is thinking\033[0m 💭️\n",
			time_since, id +1);
	else if (action == DIED)
		printf("\033[31m%ld \033[0;31mphilo[%d] died \033[0m💀️\n",
			time_since, id +1);
	else if (action == FORK)
		printf("\033[1m%ld \033[0;93mphilo[%d] has taken a fork\033[0m 🍴️\n",
			time_since, id +1);
	else if (action == FORK_LEFT)
		printf("\033[1m%ld\033[0;35m philo[%d] has left a fork\033[0m\n",
			time_since, id +1);
	else if (action == FED)
		printf("\033[32m%ld Each philo ate %i times and it's full\033[0m ⭐️\n",
			time_since, data->nb_meals);
}
