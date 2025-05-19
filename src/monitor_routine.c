/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:17:21 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/19 18:03:10 by ckappe           ###   ########.fr       */
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
	i = -1;
	cur = get_current_time();
	while (++i < table->num_of_philos)
	{
		if (cur > table->philos[i].time_next_meal)
		{
			set_dead(philo, table);
			break ;
		}
		if (philo[i].meals_eaten == philo[i].num_times_to_eat)
		{
			if (philo->num_times_to_eat == 0)
				break ;
		}
	}
	return (0);
}
