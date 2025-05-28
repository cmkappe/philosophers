/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:06:50 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/28 14:34:44 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int sim_check(t_table *table)
{
	return (get_int_locked(&table->dead_flag, &table->dead_lock));
}

int get_int_locked(int *ptr, pthread_mutex_t *lock)
{
    int v;
    pthread_mutex_lock(lock);
    v = *ptr;
    pthread_mutex_unlock(lock);
    return v;
}

void set_int_locked(int *ptr, pthread_mutex_t *lock, int value)
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

void set_size_t_locked(size_t *ptr, pthread_mutex_t *lock, size_t value)
{
	pthread_mutex_lock(lock);
	*ptr = value;
	pthread_mutex_unlock(lock);
}


/* uint64_t	read_time(t_data *data, uint64_t value)
{
	uint64_t	res;

	pthread_mutex_lock(&data->monitor);
	res = value;
	pthread_mutex_unlock(&data->monitor);
	return (res);
} */

/* 
Ensure that all threads are created before starting the simulation, otherwise, you have to wait until all threads are ready.
	while (!create_threads())
	
	;
 */



