/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:32:34 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/06 18:23:49 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	safe_atoi(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '\0')
		return (-1);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		result = result * 10 + (str[i] - '0');
		// if (result > 200)
		// 	return (-1);
		i++;
	}
	if (result == 0)
		return (-1);
	return ((int)result);
}

static long	safe_atol(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '\0')
		return (-1);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		result = result * 10 + (str[i] - '0');
		// if (result < 0)
		// 	return (-1);
		i++;
	}
	if (result == 0)
		return (-1);
	return (result);
}

void	init_data(int ac, const char **av)
{
	int		i;
	t_philo	philo;

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
	philo = init_philo(ac, av);
	write(1, "Initialization successful.\n", 27);
 }

t_philo	init_philo(int ac, const char **av)
{
	t_philo	philo;

	philo.num_of_philos = safe_atoi(av[1]);
	philo.time_to_die = safe_atol(av[2]);
	philo.time_to_eat = safe_atol(av[3]);
	philo.time_to_sleep = safe_atol(av[4]);
	philo.min_meals = -1;
	if (ac == 6)
		philo.min_meals = safe_atol(av[5]);
	return (philo);
}
