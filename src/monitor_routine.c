/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:17:21 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/20 16:55:23 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	set_dead(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(philo->dead_lock);
	philo->table->dead_flag = 1;
	print_action(philo, table, "died");
	pthread_mutex_unlock(philo->dead_lock);
}

void	*monitor_routine(void *data)
{
	int		i;
	size_t	cur;
	t_table	*table;
	t_philo	*philo;

	table = (t_table *)data;
	philo = table->philos;
	while (true)
	{
		i = -1;
		while (++i < table->num_of_philos)
		{
			// printf("DEGUG\n");
			cur = get_current_time() - table->start_time;
			if (cur > table->philos[i].time_next_meal)
			{
				printf("time for next meal: %zu\n", table->philos[i].time_next_meal);
				set_dead(philo, table);
				exit(EXIT_SUCCESS);
			}
			// if (philo->num_times_to_eat == 0)
			// 	break ;
	/* 		if (table->min_meals > 0 && philo[i].meals_eaten >= (int)table->min_meals)
			{
				pthread_mutex_lock(philo->meal_lock);
				if (philo->num_times_to_eat == 0)
				{
					pthread_mutex_unlock(philo->meal_lock);
					break ;
				}
				pthread_mutex_unlock(philo->meal_lock);
			} */
		}
	}
	return (0);
}
