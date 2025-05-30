/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:16:33 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/30 17:49:19 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

	// Even-ID Philosophers (P0, P2): Pick up the left fork first, then the right fork.
	// Odd-ID Philosophers (P1, P3): Pick up the right fork first, then the left fork.

static void	single_philo(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(philo->l_fork);
	print_action(philo, table, "has taken a fork");
	while (!sim_check(table))
		ft_usleep(100);
	pthread_mutex_unlock(philo->l_fork);
	return ;
}

static void multiple_philo(t_philo *philo, t_table *table)
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

static void	_take_forks(t_philo *philo, t_table *table)
{
	if (table->num_of_philos == 1)
		single_philo(philo, table);
	else
		multiple_philo(philo, table);
}

static void	_start_eating(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(philo->meal_lock);
	philo->meals_eaten++;
	philo->time_next_meal = get_current_time() - table->start_time
			+ table->time_to_die;
	pthread_mutex_unlock(philo->meal_lock);

	print_action(philo, table, "is eating");

/* 	pthread_mutex_lock(&table->meal_lock);
	philo->time_next_meal = get_current_time() - table->start_time
			+ table->time_to_die;
	pthread_mutex_unlock(&table->meal_lock); */
	ft_usleep(table->time_to_eat);


	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
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
