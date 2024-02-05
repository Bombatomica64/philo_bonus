/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:10:41 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/05 11:19:02 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <semaphore.h>
# include "../philo/philo.h"

typedef struct s_philo_bonus
{
	int					id; // Philosopher id.
	int					nb_meals; // Number of meals left to eat.
	pid_t				pid; // Philosopher pid.
	pthread_t			thread; // Philosopher thread.
	pthread_t			end; // Philosopher end thread.
	t_time				life_left; // Time left before death.
	t_bool				dead; // Boolean for death.
	t_bool				overfed; // Boolean for fed.
}	t_philo_bonus;

typedef struct s_data_bonus
{
	int					dead_nbr; // id of the dead philosopher.
	t_bool				go_on_b; // Boolean for continuing.
	int					nb_philo; // Number of philosophers.
	int					time_to_die; // Time in ms before a philosopher dies.
	int					time_to_eat; // Time in ms for a philosopher to eat.
	int					time_to_sleep; // Time in ms for a philosopher to sleep.
	int					nb_meals; // Number of meals to eat before stopping.
	pthread_t			eaten; // Thread for checking if all philo have eaten.
	t_time				time; // Time struct.
	t_philo_bonus		*philo; // Philosopher struct.
	sem_t				*forks; // Semaphore for forks.
	sem_t				*print; // Semaphore for printing.
	sem_t				*go_on; // Semaphore for continuing.
	sem_t				*end; // Semaphore for ending.
	sem_t				*fed; // Semaphore for fed.
}	t_data_bonus;

typedef struct s_data_id_bonus
{
	t_data_bonus		*data; // Data struct.
	int					id; // Philosopher id.
}	t_id;

typedef long long	t_long;

/**
 * @brief Prints the action of a philosopher in the dining simulation.
 *
 * This function prints the action of a philosopher in the dining simulation
 * based on the provided parameters.
 *
 * @param data Pointer to the data structure holding 
 * simulation parameters and state.
 * @param action The action performed by the philosopher 
 * (EAT, SLEEP, THINK, DIED, FORK, FORK_LEFT, FED).
 * @param id The ID of the philosopher performing the action.
 * @param time_s The time elapsed since the start of the simulation (in seconds).
 */
void	print_bonus(t_data_bonus *data, t_action action, int id, long time_s);

/**
 * @brief Prints the action of a philosopher with additional formatting.
 *
 * This function prints the action of a philosopher with additional formatting
 * based on the provided parameters.
 *
 * @param action The action performed by the philosopher '
 * (EAT, SLEEP, THINK, DIED, FORK, FORK_LEFT, FED).
 * @param time_since The time elapsed since 
 * the start of the action (in milliseconds).
 * @param id The ID of the philosopher performing the action.
 * @param data Pointer to the data structure
 *  holding simulation parameters and state.
 */
void	prints_b(t_action action, long time_since, int id, t_data_bonus *data);
void	input_check_bonus(char **av, int ac, t_data_bonus *data);
void	init_data_bonus(t_data_bonus *data, int ac, char **av);
void	philo_life(t_data_bonus *data, int identificator);
t_id	*make_data_id_bonus(t_data_bonus *data, int id);
t_bool	go_on_bonus(t_data_bonus *data, t_bool stop);
void	leave_fork(t_data_bonus *all_data, int id);
void	philo_eat(t_data_bonus *data, int id);
void	take_fork(t_data_bonus *data, int id);
void	take_fork(t_data_bonus *data, int id);
void	make_semaphores(t_data_bonus *data);
void	ft_close_bonus(t_data_bonus *data);
void	make_processes(t_data_bonus *data);
void	get_start_bonus(t_time *start);
int		ft_atoi_bonus(const char *str);
void	post_food(t_data_bonus *data);
void	ft_msleep_bonus(int time);
void	*check_death(void *arg);
void	*philo_eaten(void *arg);

/**
 * @brief Check if the simulation has ended elsewhere.
 * @param arg The data struct.
 * @return void* NULL.
*/
void	*check_end(void *arg);
t_long	ft_get_time_bonus(t_time *start);

#endif