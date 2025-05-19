/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:32:04 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/19 15:55:10 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	main(int ac, const char **av)
{
	//t_philo			config;
	t_philo			philos[200];
	t_table			table;
	pthread_mutex_t	forks[200];

	// philos = NULL;
	check_input(ac, av);
	init_table(ac, av, &table);
	init_philo(philos, forks, &table);
	if (!create_threads(philos, &table))
		return (-1);
	return (0);
}




/* if (!init_data(ac, av))
return (-1);
config = init_philo(ac, av);
if (!init_philo_struct(philos, forks, &table, config)) */
