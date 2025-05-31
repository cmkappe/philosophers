/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:06:50 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/31 17:55:50 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	sim_check(t_table *table)
{
	return (get_int_locked(&table->dead_flag, &table->dead_lock));
}

void	*monitor_routine(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	while (!sim_check(table))
	{
		check_for_dead(table);
		if (table->min_meals > 0)
			check_if_ate(table);
		ft_usleep(1);
	}
	return (NULL);
}

// Even-ID Philosophers (P0, P2):
//		Pick up the left fork first, then the right fork.
// Odd-ID Philosophers (P1, P3):
//		Pick up the right fork first, then the left fork.

void	single_philo(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(philo->l_fork);
	print_action(philo, table, "has taken a fork");
	while (!sim_check(table))
		ft_usleep(100);
	pthread_mutex_unlock(philo->l_fork);
	return ;
}

void	multiple_philo(t_philo *philo, t_table *table)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		print_action(philo, table, "has taken a fork");
		if (philo->r_fork)
		{
			pthread_mutex_lock(philo->r_fork);
			print_action(philo, table, "has taken a fork");
		}
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_action(philo, table, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		print_action(philo, table, "has taken a fork");
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
