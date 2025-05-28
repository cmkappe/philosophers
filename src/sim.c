/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:06:50 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/28 12:42:43 by chiarakappe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int sim_check(t_table *table)
{
	int res;
	
	pthread_mutex_lock(&table->dead_lock);
	res = table->dead_flag;
	pthread_mutex_unlock(&table->dead_lock);

	return (res);
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



