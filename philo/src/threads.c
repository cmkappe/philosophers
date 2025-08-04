/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:14:14 by ckappe            #+#    #+#             */
/*   Updated: 2025/08/04 17:45:15 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

size_t	get_locked(size_t *ptr, pthread_mutex_t *lock)
{
	size_t	v;

	pthread_mutex_lock(lock);
	v = *ptr;
	pthread_mutex_unlock(lock);
	return (v);
}

/* void	cleanup_threads(t_table *table)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&table->dead_lock);
	pthread_mutex_destroy(&table->meal_lock);
	pthread_mutex_destroy(&table->write_lock);
	while (++i < table->num_of_philos)
	{
		pthread_mutex_destroy(&table->philos[i].fork);
		pthread_join(table->philos[i].thread, NULL);
	}
} */

/* void	cleanup_threads(t_table *table)
{
	int	i = -1;

	i = -1;
	while (++i < table->num_of_philos)
		pthread_join(table->philos[i].thread, NULL);
	pthread_mutex_destroy(&table->dead_lock);
	pthread_mutex_destroy(&table->meal_lock);
	pthread_mutex_destroy(&table->write_lock);
	i = -1;
	while (++i < table->num_of_philos)
		pthread_mutex_destroy(&table->philos[i].fork);
} */

void	cleanup_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philos)
		pthread_join(table->philos[i].thread, NULL);
	i = -1;
	while (++i < table->num_of_philos)
		pthread_mutex_destroy(&table->philos[i].fork);
	pthread_mutex_destroy(&table->dead_lock);
	pthread_mutex_destroy(&table->meal_lock);
	pthread_mutex_destroy(&table->write_lock);
}

int	create_threads(t_table *table)
{
	int			i;

	i = -1;
	table->start_time = get_current_time();
	while (++i < table->num_of_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL,
				(void*)philo_routine, &table->philos[i]) != 0)
			return (write(2, "Error: could not create threads!\n", 34), -1);
	}
	while (monitor_routine(table))
		;
	return (0);
}
