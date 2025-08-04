/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:17:21 by ckappe            #+#    #+#             */
/*   Updated: 2025/08/04 17:46:46 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	_set_dead(t_table *table)
{
	pthread_mutex_lock(&table->dead_lock);
	table->dead_flag = true;
	pthread_mutex_unlock(&table->dead_lock);
	pthread_mutex_lock(&table->write_lock);
	pthread_mutex_unlock(&table->write_lock);
}

int	sim_check(t_table *table)
{
	bool	a;

	pthread_mutex_lock(&table->dead_lock);
	a = table->dead_flag;
	pthread_mutex_unlock(&table->dead_lock);
	return (a);
}

bool	check_for_dead(t_table *table)
{
	int		i;
	size_t	cur;
	size_t	last_meal;

	i = -1;
	while (++i < table->num_of_philos)
	{
		cur = get_current_time() - table->start_time;
		last_meal = get_locked(&table->philos[i].last_meal, &table->meal_lock);
		if (cur > (last_meal + table->time_to_die))
		{
			print_action(&table->philos[i], table, "died");
			_set_dead(table);
			return (true);
		}
	}
	return (false);
}

void	check_if_ate(t_table *table)
{
	int	i;
	int	meals;

	i = -1;
	while (++i < table->num_of_philos)
	{
		pthread_mutex_lock(&table->meal_lock);
		meals = table->philos[i].meals_eaten;
		pthread_mutex_unlock(&table->meal_lock);
		if (meals < table->min_meals)
			return ;
	}
	usleep(1);
	_set_dead(table);
}

bool	monitor_routine(t_table *table)
{
	if (check_for_dead(table))
		return (false);
	if (table->min_meals > 0)
		check_if_ate(table);
	ft_usleep(1);
	return (true);
}
