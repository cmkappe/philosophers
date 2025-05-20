/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:32:04 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/19 19:54:40 by chiarakappe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	main(int ac, const char **av)
{
	//t_philo			config;
	//t_philo			philos[200];
	//pthread_mutex_t	forks[200];
	t_table			table;

	// philos = NULL;
	check_input(ac, av);
	init_table(ac, av, &table);
	init_philo(&table);
	if (!create_threads(&table))
		return (-1);
	return (0);
}




/* if (!init_data(ac, av))
return (-1);
config = init_philo(ac, av);
if (!init_philo_struct(philos, forks, &table, config)) */
