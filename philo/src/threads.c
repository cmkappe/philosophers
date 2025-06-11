/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:14:14 by ckappe            #+#    #+#             */
/*   Updated: 2025/06/04 13:15:25 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	get_int_locked(int *ptr, pthread_mutex_t *lock)
{
	int	v;

	pthread_mutex_lock(lock);
	v = *ptr;
	pthread_mutex_unlock(lock);
	return (v);
}

void	set_int_locked(int *ptr, pthread_mutex_t *lock, int value)
{
	pthread_mutex_lock(lock);
	*ptr = value;
	pthread_mutex_unlock(lock);
}

size_t	get_size_t_locked(size_t *ptr, pthread_mutex_t *lock)
{
	size_t	v;

	pthread_mutex_lock(lock);
	v = *ptr;
	pthread_mutex_unlock(lock);
	return (v);
}

void	set_size_t_locked(size_t *ptr, pthread_mutex_t *lock, size_t value)
{
	pthread_mutex_lock(lock);
	*ptr = value;
	pthread_mutex_unlock(lock);
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
	if (pthread_create(&table->monitor, NULL,
			(void*)monitor_routine, table) != 0)
		return (write(2, "Error: could not create monitor thread!\n", 41), -1);
	while (!sim_check(table))
		ft_usleep(10);
	i = -1;
	while (++i < table->num_of_philos)
		pthread_join(table->philos[i].thread, NULL);
	pthread_join(table->monitor, NULL);
	return (0);
}
