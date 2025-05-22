/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:16:33 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/22 17:05:11 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

	// Even-ID Philosophers (P0, P2): Pick up the left fork first, then the right fork.
	// Odd-ID Philosophers (P1, P3): Pick up the right fork first, then the left fork.

static void	_take_forks(t_philo *philo, t_table *table)
{
	if (table->num_of_philos == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		print_action(philo, table, "has taken a fork");
		//ft_usleep(table->time_to_die);
		while (!philo->r_fork)
			ft_usleep(100);
		// pthread_mutex_lock(philo->r_fork);
		return;
	}

	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		//print_action(philo, "has taken a left fork");
		print_action(philo, table, "has taken a fork");
		if (philo->r_fork)
		{
			pthread_mutex_lock(philo->r_fork);
			//print_action(philo, "has taken a right fork");
			print_action(philo, table, "has taken a fork");
		}
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_action(philo, table, "has taken a fork");
		//print_action(philo, table, "has taken a right fork");
		pthread_mutex_lock(philo->l_fork);
		//print_action(philo, table, "has taken a left fork");
		print_action(philo, table, "has taken a fork");
	}
}

/* void	unlock_forks(t_philo *philo)
{
	
	
} */

static void	_start_eating(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(philo->meal_lock);
	philo->meals_eaten++;
	philo->time_next_meal = get_current_time() - table->start_time + table->time_to_die;
	pthread_mutex_unlock(philo->meal_lock);
	print_action(philo, table, "is eating");
	ft_usleep(table->time_to_eat);


	pthread_mutex_unlock(philo->r_fork);
	// print_action(philo, "put down the right fork");
	//print_action(philo, "has left a fork");
	pthread_mutex_unlock(philo->l_fork);
	//print_action(philo, "has left a fork");
	// print_action(philo, "put down the left fork");
}

static void	_start_sleeping(t_philo *philo, t_table *table)
{
	print_action(philo, table, "is sleeping");
	ft_usleep(table->time_to_sleep);
}

static void	_start_thinking(t_philo *philo, t_table *table)
{
	print_action(philo, table, "is thinking");
	ft_usleep(5);
}



void *philo_routine(void *data)
{
	t_table	*table;
	t_philo	*philo;

	philo = (t_philo *)data;
	table = philo->table;
	if (philo->id % 2 == 1)
	{
		_start_thinking(philo, table);
		ft_usleep(table->time_to_eat / 2);
	}
	while (!sim_check(table))
	{
		_take_forks(philo, table);
		if (sim_check(table))
			break ;
		_start_eating(philo, table);
		if (sim_check(table))
			break ;
		_start_sleeping(philo, table);
		if (sim_check(table))
			break ;
		_start_thinking(philo, table);
	}
	return NULL;
}




// 3.2. Limit Holding Time: in this strategy, you will prevent the deadlock by setting a Time Limit. 
// If a philosopher can’t get both forks within a certain time, they must release any forks they have and try again later. 
// This prevents them from waiting forever.




// monitor checks if anybody died or everybody ate => sim stop

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