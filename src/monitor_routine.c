/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:17:21 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/07 17:26:19 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*monitor_routine(t_philo *philo, t_table *table)
{
	(void)philo;
	(void)table;
	return (0);
}

/* This thread will be running and monitoring the whole program, it has 2 checks in it that run infinitely 
until a philo dies or they all ate the number of meals they need to (last input argument). 
Basically, we will check that the time a philo needs to die didn’t surpass the last meal he had and that he is not concurrently eating. 
If he indeed died we change the dead flag to 1 and that will break the loop in all of the threads. 
The other check is to see if all the philos finished eating the amount of meals they need to, 
and if they did we will again change the dead flag to one and break the threads loop. */

/* pthread_mutex_lock(&table->dead_lock);
if (table->dead_flag || (philo->num_times_to_eat > 0 &&
		philo->meals_eaten >= philo->num_times_to_eat))
	{
		pthread_mutex_unlock(&table->dead_lock);
		break ;
	}
pthread_mutex_unlock(&table->dead_lock); */