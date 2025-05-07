/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:16:33 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/07 17:29:53 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	print_action(t_philo *philo, const char *action)
{
	pthread_mutex_lock(philo->write_lock);
	printf("[%zu] %d %s\n", get_current_time() - philo->start_time, philo->id, action);
	pthread_mutex_unlock(philo->write_lock);
}

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(1000);

	pthread_mutex_lock(philo->l_fork);
	print_action(philo, "has taken a left fork");

	pthread_mutex_lock(philo->r_fork);
	print_action(philo, "has taken a right fork");
}

/* void	unlock_forks(t_philo *philo)
{
	
	
} */


void *philo_routine(void *data)
{
	t_table	*table;
	t_philo	*philo;
	
	philo = (t_philo *)data;
	table = philo->table;
	//size_t	cur_time;
	printf("----------Debug-------------\n");
	while (1)
	{
		take_forks(philo);
	
	}
	return NULL;
}


	// pthread_mutex_lock(&table->meal_lock);
	// printf ("hello im philo num %d\n", philo->id);
	// pthread_mutex_unlock(&table->meal_lock);
	// pthread_mutex_lock(philo->l_fork);
	// printf ("hello im philo num %d and i got the left fork\n", philo->id);
	// usleep(10000);
	// pthread_mutex_unlock(philo->l_fork);
	// pthread_mutex_lock(&table->meal_lock);
	// printf ("hello im philo num %d and i left the left fork\n", philo->id);
	// pthread_mutex_unlock(&table->meal_lock);



	//while (!table.dead_flag)
	// {
	// 	take_forks(philo);
	// 	eat(philo);
	// 	put_forks(philo);
	// 	sleep(philo);
	// 	think();
	// }
	// pthread_mutex_lock(&table.meal_lock);
	// cur_time = get_time_in_ms() - philo.start_time;
	// printf ("num of philos: %d\n", table.philos->num_of_philos);
	// printf ("start time: %d\n", philo.start_time);
	// take_forks(&table, data);
	// pthread_mutex_unlock(&table.meal_lock);


/* The routine will be the function executed over and over by the philos, 
Basically ,I created a loop that will break as soon as the dead flag is 1, in other words as soon as a philo is dead. 

Remember:
The philosophers alternatively eat, sleep, or think. 
While they are eating, they are not thinking nor sleeping, while thinking, they are not eating nor sleeping, 
and, of course, while sleeping, they are not eating nor thinking.

So in our loop, they will eat, sleep and think. 
Let’s start with the easiest one when they think we just need to print a message “X is thinking” (X is the philo number),
When they sleep we need to make them sleep the length of the input inserted 
by the user using our ft_usleep (described in the bottom of this page) and then print the message “X is sleeping”. 
Now to the eating part, We will lock the right fork first using pthread_mutex_lock and print the message, and do the same with the left fork. 
Then he will eat using ft_usleep again and only then he will drop the forks by unlocking the locks, 
before that we change some variables that give our monitor indications but that’s the general idea. */