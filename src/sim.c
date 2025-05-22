/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:06:50 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/22 22:04:43 by chiarakappe      ###   ########.fr       */
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

/* 
Ensure that all threads are created before starting the simulation, otherwise, you have to wait until all threads are ready.
	while (!create_threads())
	
	;










 */



