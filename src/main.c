/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:32:04 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/04 15:14:30 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	main(int ac, const char **av)
{
	t_philo			config;
	t_philo			philos[200];
	t_table			table;
	pthread_mutex_t	forks[200];

	init_data(ac, av);
	config = init_philo(ac, av);
	init_philo_struct(philos, forks, &table, config);
	init_table_struct(&table);
	return (0);
}
