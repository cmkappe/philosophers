/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:32:04 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/30 17:28:05 by ckappe           ###   ########.fr       */
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
	if (check_input(ac, av) < 0)
		return (EXIT_FAILURE);
	if (init_table(ac, av, &table) < 0)
		return (EXIT_FAILURE);
	init_philo(&table);
	if (!create_threads(&table))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}




/* if (!init_data(ac, av))
return (-1);
config = init_philo(ac, av);
if (!init_philo_struct(philos, forks, &table, config)) */
