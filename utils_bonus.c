/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:39:01 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/01 17:52:46 by lmicheli         ###   ########.fr       */
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
