/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:17:21 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/22 16:45:00 by ckappe           ###   ########.fr       */
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

void	check_for_dead(t_table *table)
{
	int	i;
	size_t	cur;
	
	i = -1;
	while (++i < table->num_of_philos)
	{
		cur = get_current_time() - table->start_time;
		// printf("cur time: %zu\n", cur);
		// printf("philo number :%d time_next_meal: %zu\n",table->philos[i].id, table->philos[i].time_next_meal);
		if (cur > table->philos[i].time_next_meal)
		{
			set_dead(&table->philos[i], table);
			exit(EXIT_SUCCESS);
		}
	}
}

static void	check_if_ate(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philos)
	{
		if (!(table->philos[i].meals_eaten >= table->min_meals))
		return ;
	}
	printf("DEBUG\n");
	//exit(EXIT_SUCCESS);
	pthread_mutex_lock(&table->dead_lock);
	table->dead_flag = 1;
	pthread_mutex_lock(&table->dead_lock);
}

void	*monitor_routine(void *data)
{
	t_table	*table;
	t_philo	*philo;

	table = (t_table *)data;
	philo = table->philos;
	while (true)
	{
		check_for_dead(table);
		if (table->min_meals > 0)
		{
			check_if_ate(table);
		}
	}
	return (0);
}
