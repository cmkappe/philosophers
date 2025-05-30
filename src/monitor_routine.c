/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:17:21 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/30 16:19:49 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

/* static void	set_dead(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(philo->dead_lock);
	pthread_mutex_lock(philo->write_lock);
	print_action(philo, table, "died");
	philo->table->dead_flag = 1;
	pthread_mutex_unlock(philo->dead_lock);
	pthread_mutex_unlock(philo->write_lock);

} */

static void	_set_dead(t_table *table)
{
	set_int_locked(&table->dead_flag, &table->dead_lock, 1);
}

void	check_for_dead(t_table *table)
{
	int	i;
	size_t	cur;
	size_t	next_meal;

	i = -1;
	while (++i < table->num_of_philos)
	{
		cur = get_current_time() - table->start_time;

		next_meal = get_size_t_locked(&table->philos[i].time_next_meal,
				&table->meal_lock);
		if (cur > next_meal)
		{
			print_action(&table->philos[i], table, "died");
			_set_dead(table);
			return ;
		}
	}
}

static void	_check_if_ate(t_table *table)
{
	int	i;
	int	meals;

	i = -1;
	while (++i < table->num_of_philos)
	{
		pthread_mutex_lock(table->philos[i].meal_lock);
		meals = table->philos[i].meals_eaten;
		pthread_mutex_unlock(table->philos[i].meal_lock);
		if (meals < table->min_meals)
			return ;
	}
	set_int_locked(&table->dead_flag, &table->dead_lock, 1);
}

void	*monitor_routine(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	while (!sim_check(table))
	{
		check_for_dead(table);
		if (table->min_meals > 0)
			_check_if_ate(table);
		ft_usleep(1);
	}
	return NULL;
}
