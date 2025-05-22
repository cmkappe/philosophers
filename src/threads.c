/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:14:14 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/22 22:36:24 by chiarakappe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	create_threads(t_table *table)
{
	int			i;

	i = -1;
	table->start_time = get_current_time();
	while (++i < table->num_of_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL,
				(void*)philo_routine, &table->philos[i]) != 0)
			return (write(2, "Error: could not create threads!\n", 34), -1);
	}
	if (pthread_create(&table->monitor, NULL,
			(void*)monitor_routine, table) != 0)
		return (write(2, "Error: could not create monitor thread!\n", 41), -1);
	while (!sim_check(table))
		ft_usleep(100);
	i = -1;
	while (++i < table->num_of_philos)
		pthread_join(table->philos[i].thread, NULL);
	 return (0);
}
