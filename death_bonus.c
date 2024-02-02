/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:48:57 by lmicheli          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/02 15:10:43 by mruggier         ###   ########.fr       */
=======
/*   Updated: 2024/02/01 18:27:22 by lmicheli         ###   ########.fr       */
>>>>>>> 613cd5b0ec4773c79bef7c8fd8b6b77385c49369
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_close_bonus(t_data_bonus *data)
{
	(void)data;
	sem_close(data->forks);
<<<<<<< HEAD
	//free(data->forks);
	sem_close(data->end);
	//free(data->end);
	sem_close(data->print);
	//free(data->print);
	sem_close(data->go_on);
	//free(data->go_on);
	
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("dead");
	sem_unlink("eat");
	sem_unlink("end");
	
=======
//	free(data->forks);
	sem_close(data->end);
//	free(data->end);
	sem_close(data->print);
//	free(data->print);
	sem_close(data->go_on);
//	free(data->go_on);
>>>>>>> 613cd5b0ec4773c79bef7c8fd8b6b77385c49369
	free(data->philo);
	free(data);
	// kill(0, SIGTERM);
	exit(EXIT_SUCCESS);
}

t_bool	go_on_bonus(t_data_bonus *data, t_bool stop)
{
	sem_wait(data->go_on);
	if (stop == TRUE)
	{
		sem_post(data->go_on);
		return (FALSE);
	}
	else
	{
		sem_post(data->go_on);
		return (TRUE);
	}
}

void	*check_death(void *arg)
{
	t_id	*data;

	data = (t_id *)arg;
	while (data->data->philo[data->id].go_on == TRUE)
	{
		data->data->philo[data->id]
			.life_left.time_since = ft_get_time_bonus(&data->data->time);
		if (data->data->philo[data->id]
			.life_left.time_since > data->data->time_to_die)
		{
			data->data->philo[data->id].go_on = FALSE;
			print_bonus(data->data, DIED, data->id,
				ft_get_time_bonus(&data->data->time));
<<<<<<< HEAD
			printf("\033[37m%s\n\033[0m", "morto");
			sem_wait(data->data->end);
=======
			sem_post(data->data->end);
>>>>>>> 613cd5b0ec4773c79bef7c8fd8b6b77385c49369
			return (NULL);
		}
		if (sem_wait(data->data->end) != -1)
		{
			sem_post(data->data->end);
			data->data->philo[data->id].go_on = FALSE;
			return (NULL);
		}
	}
	return (NULL);
}
