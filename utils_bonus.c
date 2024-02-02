/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:39:01 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/02 15:23:27 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_id	*make_data_id_bonus(t_data_bonus *data, int id)
{
	t_id	*data_id;

	data_id = malloc(sizeof(t_id));
	data_id->data = data;
	data_id->id = id;
	return (data_id);
}

t_bool	go_on_bonus(t_data_bonus *data, t_bool stop)
{
	t_bool	go_on;
	
	sem_wait(data->go_on);
	if (stop == TRUE)
	{
		data->go_on_b = FALSE;
		sem_post(data->go_on);
		return (FALSE);
	}
	else
	{
		go_on = data->go_on_b;
		sem_post(data->go_on);
		return (go_on);
	}
}