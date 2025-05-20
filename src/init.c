/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:32:34 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/19 20:05:31 by chiarakappe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	check_input(int ac, const char **av)
{
	int		i;

	if (!(ac == 5 || ac == 6))
	{
		write(2, "Error: Invalid number of arguments.", 36);
		write(2, " Expected 4 or 5 arguments.\n", 29);
		exit(EXIT_FAILURE);
	}
	if (safe_atoi(av[1]) > 200)
	{
		write(2, "Error: Number of philosophers cannot exceed 200.\n", 50);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (++i < ac)
	{
		if (safe_atol(av[i]) <= 0)
		{
			write(2, "Error: All arguments must be positive integers.\n", 49);
			exit(EXIT_FAILURE);
		}
	}
	write(1, "Initialization successful.\n", 27);
}

void	init_table(int ac, const char **av, t_table *table)
{
	table->num_of_philos = safe_atoi(av[1]);
	table->time_to_die = safe_atol(av[2]);
	table->time_to_eat = safe_atol(av[3]);
	table->time_to_sleep = safe_atol(av[4]);
	//philo.min_meals = -1;
	if (ac == 6)
		table->min_meals = safe_atol(av[5]);
	else
		table->min_meals = -1;
		table->dead_flag = 0;
	pthread_mutex_init(&table->dead_lock, NULL);
	pthread_mutex_init(&table->meal_lock, NULL);
	pthread_mutex_init(&table->write_lock, NULL);
}

void	init_philo(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philos)
		pthread_mutex_init(table->philos[i].l_fork, NULL);
	i = -1;
	while (++i < table->num_of_philos)
	{
		table->philos[i].id = i + 1;
		//table->philos[i].eating = 0;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal = get_current_time();
		table->philos[i].time_next_meal = table->time_to_die;
	// ???	table->philos[i].start_time = table->philos[i].last_meal;
		table->philos[i].dead = &table->dead_flag;
		table->philos[i].write_lock = &table->write_lock;
		table->philos[i].dead_lock = &table->dead_lock;
		table->philos[i].meal_lock = &table->meal_lock;
		table->philos[i].l_fork = table->philos[i].l_fork;
		table->philos[i].r_fork = table->philos[(i + 1) % table->num_of_philos].r_fork;
		table->philos[i].thread = 0;
		table->philos[i].table = table;
	}
}

/* void	init_table_struct(t_table *table)
{
	table->dead_flag = 0;
	pthread_mutex_init(&table->dead_lock, NULL);
	pthread_mutex_init(&table->meal_lock, NULL);
	pthread_mutex_init(&table->write_lock, NULL);
} */