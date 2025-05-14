/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:17:21 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/14 22:15:22 by chiarakappe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*monitor_routine(void *data)
{
	int		i;
	size_t	cur;
	//t_table	*table;
	t_philo	*philo;
	
	philo = (t_philo *)data;
	//table = philo->table;
	i = -1;
	cur = get_current_time() - philo->start_time;
	while (++i < philo->num_of_philos)
	{
		if (cur > philo[i].time_to_die)
		{
			pthread_mutex_lock(philo[i].dead_lock);
			philo->table->dead_flag = 1;
			print_action(philo, "died");
			pthread_mutex_unlock(philo[i].dead_lock);
			break ;
		}
		if (philo[i].meals_eaten == philo[i].num_times_to_eat)
		{
			printf("philo id %d num times to eat: %d\n", philo->id, philo->num_times_to_eat);
			if (philo->num_times_to_eat == 0)
				break ;
		}
	}
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


/* 	while (1)
	{
		take_forks(philo);
		start_eating(philo);
		if (philo->num_times_to_eat > 0)
		{
			philo->num_times_to_eat--;
			printf("philo id %d num times to eat: %d\n", philo->id, philo->num_times_to_eat);
			if (philo->num_times_to_eat == 0)
				break ;
		}
		start_sleeping(philo);
		start_thinking(philo);
	} */


