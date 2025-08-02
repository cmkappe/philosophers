/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:32:04 by ckappe            #+#    #+#             */
/*   Updated: 2025/08/02 19:35:33 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void cleanup(t_table *table)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&table->dead_lock);
	pthread_mutex_destroy(&table->meal_lock);
	pthread_mutex_destroy(&table->write_lock);
	while (++i < table->num_of_philos)
	{
		pthread_mutex_destroy(&table->philos[i].fork);
		pthread_join(table->philos[i].thread, NULL);
	}

}

int	main(int ac, const char **av)
{
	t_table			table;
	int				i;

	i = 0;
	if (check_input(ac, av) < 0)
		return (EXIT_FAILURE);
	if (init_table(ac, av, &table) < 0)
		return (EXIT_FAILURE);
	init_philo(&table);
	if (create_threads(&table) < 0)
		return (EXIT_FAILURE);
	cleanup(&table);
	return (EXIT_SUCCESS);
}
