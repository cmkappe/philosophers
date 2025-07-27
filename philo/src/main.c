/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:32:04 by ckappe            #+#    #+#             */
/*   Updated: 2025/07/27 13:07:59 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

/* void	*monitor_range(void *arg)
{
	t_monitor_args	*args;
	int				i;

	args = (t_monitor_args *)arg;
	while (!sim_check(args->table))
	{
		i = args->start;
		while (i <= args->end)
		{
			if (check_for_dead(&args->table->philos[i]))
				return (NULL);
			i++;
		}
		ft_usleep(10); // short sleep to reduce CPU load
	}
	return (NULL);
} */


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
	return (EXIT_SUCCESS);
}

