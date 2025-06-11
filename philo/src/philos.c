/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:16:33 by ckappe            #+#    #+#             */
/*   Updated: 2025/06/09 16:41:43 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	take_forks(t_philo *philo, t_table *table)
{
	if (table->num_of_philos == 1)
		single_philo(philo, table);
	else
		multiple_philo(philo, table);
}

void	start_eating(t_philo *philo, t_table *table)
{
	size_t	now_rel;

	pthread_mutex_lock(philo->meal_lock);
	philo->meals_eaten++;
	now_rel = get_current_time() - table->start_time;
	philo->time_next_meal = now_rel + table->time_to_die;
	pthread_mutex_unlock(philo->meal_lock);
	print_action(philo, table, "is eating");
	ft_usleep(table->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	start_sleeping(t_philo *philo, t_table *table)
{
	print_action(philo, table, "is sleeping");
	ft_usleep(table->time_to_sleep);
}

void	start_thinking(t_philo *philo, t_table *table)
{
	print_action(philo, table, "is thinking");
	ft_usleep(5);
}
