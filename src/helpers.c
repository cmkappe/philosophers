/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:20:10 by ckappe            #+#    #+#             */
/*   Updated: 2025/06/04 13:48:45 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	print_action(t_philo *philo, t_table *table, const char *action)
{
	size_t	now;

	if (get_int_locked(&table->dead_flag, &table->dead_lock) != 0)
		return ;
	now = get_current_time() - table->start_time;
	pthread_mutex_lock(philo->write_lock);
	printf("%zu %d %s\n", now, philo->id, action);
	pthread_mutex_unlock(philo->write_lock);
}

int	safe_atoi(const char *str)
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
		if (result > INT_MAX)
			return (-1);
		i++;
	}
	if (result == 0)
		return (-1);
	return ((int)result);
}

long	safe_atol(const char *str)
{
	int		i;
	long	res;
	long	m;

	i = 0;
	res = 0;
	m = LONG_MAX / 10;
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
		if (res > m || (res == m && (str[i] - '0') > LONG_MAX % 10))
			return (-1);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (res == 0)
		return (-1);
	return (res);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
