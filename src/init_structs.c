/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:49:31 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/06 18:24:13 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	init_philo_struct(t_philo *philos, pthread_mutex_t *forks,
			t_table *table, t_philo conf)
{
	int	i;

	i = -1;
	while (++i < conf.num_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = get_time_in_ms();
		philos[i].start_time = philos[i].last_meal;
		philos[i].num_of_philos = conf.num_of_philos;
		philos[i].time_to_die = conf.time_to_die;
		philos[i].time_to_eat = conf.time_to_eat;
		philos[i].time_to_sleep = conf.time_to_sleep;
		philos[i].num_times_to_eat = conf.min_meals;
		philos[i].dead = &table->dead_flag;
		philos[i].write_lock = &table->write_lock;
		philos[i].dead_lock = &table->dead_lock;
		philos[i].meal_lock = &table->meal_lock;
		philos[i].l_fork = &forks[i];
		philos[i].r_fork = &forks[(i + 1) % conf.num_of_philos];
		philos[i].thread = 0;
	}
}

void	init_table_struct(t_table *table)
{
	table->dead_flag = 0;
	pthread_mutex_init(&table->dead_lock, NULL);
	pthread_mutex_init(&table->meal_lock, NULL);
	pthread_mutex_init(&table->write_lock, NULL);
}
