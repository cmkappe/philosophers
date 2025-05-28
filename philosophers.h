/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:32:57 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/27 00:44:29 by chiarakappe      ###   ########.fr       */
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
	size_t			last_meal;
	int				num_times_to_eat;
	int				id;
	int				eating;
	int				meals_eaten;
	int				*dead;
	size_t			time_next_meal;
	pthread_mutex_t	fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	struct s_table	*table;
}				t_philo;

typedef struct s_table
{
	t_philo			philos[200];
	pthread_t		monitor;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	int				dead_flag;
	int				num_of_philos;
	size_t			start_time;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				min_meals;
}				t_table;


/* *****************************  INIT  ****************************** */
void	check_input(int ac, const char **av);
// void	init_args(int ac, const char **av);
void	init_table(int ac, const char **av, t_table *table);
void	init_philo(t_table *table);

int		create_threads(t_table *table);

/* *****************************  SIM  ****************************** */
void	*philo_routine(void *data);
void	*monitor_routine(void *data);

void	start_eating(t_philo *philo, t_table *table);
void	start_sleeping(t_philo *philo, t_table *table);

int 	sim_check(t_table *table);

/* *****************************  SIM  ****************************** */
int   	get_int_locked(int *ptr, pthread_mutex_t *lock);
void  	set_int_locked(int *ptr, pthread_mutex_t *lock, int value);
size_t 	get_size_t_locked(size_t *ptr, pthread_mutex_t *lock);
void  	set_size_t_locked(size_t *ptr, pthread_mutex_t *lock, size_t value);


/* ****************************  HELPERS  ***************************** */
int		ft_usleep(size_t milliseconds);
size_t	get_current_time(void);
void	print_action(t_philo *philo, t_table *table, const char *action);
int		safe_atoi(const char *str);
long	safe_atol(const char *str);

#endif
