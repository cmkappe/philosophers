/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:06:50 by ckappe            #+#    #+#             */
/*   Updated: 2025/08/02 17:02:38 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static inline bool	unlock_if_stopped(pthread_mutex_t *fork, t_table *table)
{
	if (sim_check(table))
	{
		pthread_mutex_unlock(fork);
		return (true);
	}
	return (false);
}

void	single_philo(t_philo *philo, t_table *table)
{
	if (print_action(philo, table, "has taken a fork"))
		return ;
	pthread_mutex_lock(philo->l_fork);
	while (!sim_check(table))
		ft_usleep(10);
	pthread_mutex_unlock(philo->l_fork);
	return ;
}

// Even-ID Philosophers (P0, P2):
//		Pick up the left fork first, then the right fork.
// Odd-ID Philosophers (P1, P3):
//		Pick up the right fork first, then the left fork.

void	even_num_of_philos(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(philo->l_fork);
	print_action(philo, table, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	print_action(philo, table, "has taken a fork");
}

void	multiple_philo(t_philo *philo, t_table *table)
{
	if (table->num_of_philos % 2 == 0)
		even_num_of_philos(philo, table);
	else
	{
		if (philo->r_fork)
		{
			pthread_mutex_lock(philo->r_fork);
			if (print_action(philo, table, "has taken a fork"))
			{
				unlock_if_stopped(philo->r_fork, table);
				return ;
			}
		}
		pthread_mutex_lock(philo->l_fork);
		if (print_action(philo, table, "has taken a fork"))
		{
			unlock_if_stopped(philo->l_fork, table);
			if (philo->r_fork)
				pthread_mutex_unlock(philo->r_fork);
			return ;
		}
	}
}

void	*philo_routine(void *data)
{
	t_table	*table;
	t_philo	*philo;

	philo = (t_philo *)data;
	table = philo->table;
	if (philo->id % 2 == 1)
	{
		start_thinking(philo, table);
		ft_usleep(table->time_to_eat / 2);
	}
	while (!sim_check(table))
	{
		take_forks(philo, table);
		if (sim_check(table))
			break ;
		start_eating(philo, table);
		if (sim_check(table))
			break ;
		start_sleeping(philo, table);
		if (sim_check(table))
			break ;
		start_thinking(philo, table);
	}
	return (NULL);
}
