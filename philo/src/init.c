/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:32:34 by ckappe            #+#    #+#             */
/*   Updated: 2025/08/04 18:02:01 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	check_input(int ac, const char **av)
{
	int		i;
	long	val;

	if (!(ac == 5 || ac == 6))
	{
		write(2, "Error: Invalid number of arguments.", 36);
		write(2, " Expected 4 or 5 arguments.\n", 29);
		return (-1);
	}
	if (safe_atoi(av[1]) > 200)
	{
		write(2, "Error: Number of philosophers cannot exceed 200.\n", 50);
		return (-1);
	}
	i = 0;
	while (++i < ac)
	{
		val = safe_atol(av[i]);
		if (val <= 0 || val > INT_MAX)
			return (write(2, "Error: Arguments must be valid integers", 40),
				write(2, " within range.\n", 16), -1);
	}
	write(1, "Initialization successful.\n", 27);
	return (0);
}

int	init_table(int ac, const char **av, t_table *table)
{
	table->num_of_philos = safe_atoi(av[1]);
	table->time_to_die = (size_t)safe_atol(av[2]);
	table->time_to_eat = (size_t)safe_atol(av[3]);
	table->time_to_sleep = (size_t)safe_atol(av[4]);
	if (ac == 6)
		table->min_meals = safe_atoi(av[5]);
	else
		table->min_meals = -1;
	table->dead_flag = 0;
	if (pthread_mutex_init(&table->dead_lock, NULL) != 0
		|| pthread_mutex_init(&table->meal_lock, NULL) != 0
		|| pthread_mutex_init(&table->write_lock, NULL) != 0)
		return (write(2, "Error: Mutex init failed.\n", 27), -1);
	return (0);
}

void	init_philo(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philos)
		pthread_mutex_init(&table->philos[i].fork, NULL);
	i = -1;
	while (++i < table->num_of_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].time_next_meal = table->time_to_die;
		table->philos[i].l_fork = &table->philos[i].fork;
		if (table->num_of_philos == 1)
			table->philos[i].r_fork = NULL;
		else
			table->philos[i].r_fork = &table->philos[(i + 1)
				% table->num_of_philos].fork;
		table->philos[i].table = table;
	}
}

/* int	init_table(int ac, const char **av, t_table *table)
{
	table->num_of_philos = safe_atoi(av[1]);
	table->time_to_die = (size_t)safe_atol(av[2]);
	table->time_to_eat = (size_t)safe_atol(av[3]);
	table->time_to_sleep = (size_t)safe_atol(av[4]);
	// if (table->num_of_philos < 0 || table->time_to_die < 0
	// 	|| table->time_to_eat < 0 || table->time_to_sleep < 0)
	// {
	// 	write(2, "Error: Invalid arguments.\n", 26);
	// 	return (-1);
	// }
	if (ac == 6)
		table->min_meals = safe_atoi(av[5]);
	else
		table->min_meals = -1;
	table->dead_flag = 0;
	if (pthread_mutex_init(&table->dead_lock, NULL) != 0
		|| pthread_mutex_init(&table->meal_lock, NULL) != 0
		|| pthread_mutex_init(&table->write_lock, NULL) != 0)
		return (write(2, "Error: Mutex init failed.\n", 27), -1);
	return (0);
} */