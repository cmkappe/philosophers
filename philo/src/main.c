/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:32:04 by ckappe            #+#    #+#             */
/*   Updated: 2025/08/05 14:09:21 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	main(int ac, const char **av)
{
	t_table			table;

	if (check_input(ac, av) < 0)
		return (EXIT_FAILURE);
	if (init_table(ac, av, &table) < 0)
		return (EXIT_FAILURE);
	init_philo(&table);
	if (create_threads(&table) < 0)
		return (EXIT_FAILURE);
	cleanup_threads(&table);
	return (EXIT_SUCCESS);
}
