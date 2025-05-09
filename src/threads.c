/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:14:14 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/09 16:20:01 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

// create a thread for each philospher and one extra for the monitor
// philo thread will run philo routine function & observer will run the monitor function

int	create_threads(t_philo *philo, t_table *table)
{
	int			i;

	i = -1;
	(void)table;
	philo->start_time = get_current_time();
	while (++i < philo->num_of_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, (void*)philo_routine, &philo[i]) != 0)
			return (write(2, "Error: could not create threads!\n", 34), -1);
	}
	if (pthread_create(&table->monitor, NULL, (void*)monitor_routine, philo) != 0)
		return (write(2, "Error: could not create monitor thread!\n", 41), -1);
	i = -1;
	while (++i < philo->num_of_philos)
		pthread_join(&philo->thread[i], NULL);
	if (table->dead_flag == 1)
		print_action(philo, "died");
	return (0);
}

