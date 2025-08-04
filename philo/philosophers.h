/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:32:57 by ckappe            #+#    #+#             */
/*   Updated: 2025/08/04 17:45:21 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	fork;
	size_t			last_meal;
	int				id;
	int				meals_eaten;
	size_t			time_next_meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	struct s_table	*table;
}				t_philo;

typedef struct s_table
{
	t_philo			philos[200];
	pthread_t		monitor;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	bool			dead_flag;
	int				num_of_philos;
	size_t			start_time;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				min_meals;
}				t_table;

/* *****************************  INIT  ****************************** */
int		check_input(int ac, const char **av);
int		init_table(int ac, const char **av, t_table *table);
void	init_philo(t_table *table);

/* ******************************  SIM  ******************************* */
void	single_philo(t_philo *philo, t_table *table);
void	multiple_philo(t_philo *philo, t_table *table);
void	take_forks(t_philo *philo, t_table *table);
void	start_eating(t_philo *philo, t_table *table);
void	start_sleeping(t_philo *philo, t_table *table);
void	start_thinking(t_philo *philo, t_table *table);
void	*philo_routine(void *data);
void	check_if_ate(t_table *table);
int		sim_check(t_table *table);
bool	monitor_routine(t_table *table);
bool	check_for_dead(t_table *table);

/* *****************************  THREADS  ****************************** */
int		create_threads(t_table *table);
void	cleanup_threads(t_table *table);

/* ****************************  HELPERS  ***************************** */
size_t	get_current_time(void);
size_t	get_locked(size_t *ptr, pthread_mutex_t *lock);
void	ft_usleep(size_t milliseconds);
bool	print_action(t_philo *philo, t_table *table, const char *action);
int		safe_atoi(const char *str);
long	safe_atol(const char *str);

#endif
