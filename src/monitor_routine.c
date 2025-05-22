/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:17:21 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/22 22:34:37 by chiarakappe      ###   ########.fr       */
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
	
	i = -1;
	while (++i < table->num_of_philos)
	{
		cur = get_current_time() - table->start_time;
		// printf("cur time: %zu\n", cur);
		// printf("philo number :%d time_next_meal: %zu\n",table->philos[i].id, table->philos[i].time_next_meal);
		if (cur > table->philos[i].time_next_meal)
		{
			set_dead(table);
			print_action(&table->philos[i], table, "died");
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
