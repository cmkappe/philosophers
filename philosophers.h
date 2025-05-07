/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:32:57 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/07 15:49:02 by ckappe           ###   ########.fr       */
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

typedef struct s_philo
{
	pthread_t		thread;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			min_meals;
	size_t			last_meal;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				id;
	int				eating;
	int				meals_eaten;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	struct s_table	*table;
}				t_philo;

typedef struct s_table
{
	t_philo			*philos;
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_t		monitor;
}				t_table;


/* *****************************  INIT  ****************************** */
void	init_data(int ac, const char **av);
t_philo	init_philo(int ac, const char **av);
void	init_table_struct(t_table *table);
void	init_philo_struct(t_philo *philos, pthread_mutex_t *forks,
			t_table *table, t_philo conf);

int		create_threads(t_philo *philo, t_table *table);

/* *****************************  SIM  ****************************** */
void	*philo_routine(void *data);
void	*monitor_routine(t_philo *philo, t_table *table);

/* ****************************  HELPERS  ***************************** */
size_t	get_current_time(void);


#endif
