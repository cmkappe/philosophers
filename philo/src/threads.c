/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:14:14 by ckappe            #+#    #+#             */
/*   Updated: 2025/08/02 19:30:20 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

size_t	get_size_t_locked(size_t *ptr, pthread_mutex_t *lock)
{
	size_t	v;

	pthread_mutex_lock(lock);
	v = *ptr;
	pthread_mutex_unlock(lock);
	return (v);
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
		// ft_usleep(250);
	return (0);
}
