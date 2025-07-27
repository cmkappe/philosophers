/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:16:33 by ckappe            #+#    #+#             */
/*   Updated: 2025/07/27 18:19:25 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	take_forks(t_philo *philo, t_table *table)
{
	// if (sim_check(table))
	// 	return ;
	if (table->num_of_philos == 1)
		single_philo(philo, table);
	else
		multiple_philo(philo, table);
	// if (sim_check(table))
	// 	return ;
}

void	start_eating(t_philo *philo, t_table *table)
{

	// if (sim_check(table))
	// 	return ;
	pthread_mutex_lock(&table->meal_lock);
	philo->meals_eaten++;
	philo->last_meal = get_current_time() - table->start_time;
	pthread_mutex_unlock(&table->meal_lock);
	if (print_action(philo, table, "is eating"))
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	ft_usleep(table->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

/* void	start_eating(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&table->meal_lock);
	philo->meals_eaten++;
	philo->time_next_meal = get_current_time() + table->time_to_die;
	pthread_mutex_unlock(&table->meal_lock);
	print_action(philo, table, "is eating");
	ft_usleep(table->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
} */

void	start_sleeping(t_philo *philo, t_table *table)
{
/* 	if (sim_check(table))
	{
		//ft_usleep(10);
		return ;
	} */
	print_action(philo, table, "is sleeping");
		// return ;
	ft_usleep(table->time_to_sleep);
}

void	start_thinking(t_philo *philo, t_table *table)
{
/* 	if (sim_check(table))
	{
		//ft_usleep(10);
		return ;
	} */
	//ft_usleep(2);
	if (print_action(philo, table, "is thinking"))
	{
		return ;
	}
	ft_usleep(1);
}
