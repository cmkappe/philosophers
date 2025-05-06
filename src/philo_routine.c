/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:16:33 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/06 18:39:36 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void *philo_routine(void *data)
{
	t_philo philo;

	philo = (void)
	pthread_mutex_lock(&table->meal_lock);
	printf ("%d\n", philo->num_of_philos);
	pthread_mutex_unlock(&table->meal_lock);
	

	
	return (0);
}


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