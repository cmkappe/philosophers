/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:20:10 by ckappe            #+#    #+#             */
/*   Updated: 2025/08/02 19:49:21 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

bool	print_action(t_philo *philo, t_table *table, const char *action)
{
	size_t	now;

	pthread_mutex_lock(&table->write_lock);
	if (sim_check(table))
	{
		pthread_mutex_unlock(&table->write_lock);
		return (true);
	}
	now = get_current_time() - table->start_time;
	printf("%zu %d %s\n", now, philo->id, action);
	pthread_mutex_unlock(&table->write_lock);
	return (false);
}

int	safe_atoi(const char *str)
{
	int				i;
	int				sign;
	long long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\r' || str[i] == '\n' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') && str[i] != '\0')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
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

void	ft_usleep(size_t milliseconds)
{
	size_t	start;
	size_t	elapsed;

	start = get_current_time();
	while (1)
	{
		elapsed = get_current_time() - start;
		if (elapsed >= milliseconds)
			break ;
		if (milliseconds - elapsed > 1)
			usleep((milliseconds - elapsed) * 500);
		else
			usleep(50);
	}
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
