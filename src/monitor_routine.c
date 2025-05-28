/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:17:21 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/27 00:20:07 by chiarakappe      ###   ########.fr       */
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

static void	set_dead(t_table *table)
{
	pthread_mutex_lock(&table->dead_lock);
	table->dead_flag = 1;
	pthread_mutex_unlock(&table->dead_lock);
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

		pthread_mutex_lock(&table->meal_lock);
		next_meal = table->philos[i].time_next_meal;
		pthread_mutex_unlock(&table->meal_lock);
		if (cur > next_meal)
		{
			print_action(&table->philos[i], table, "died");
			set_dead(table);
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

	table = (t_table *)data;
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
