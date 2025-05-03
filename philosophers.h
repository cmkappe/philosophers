/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:32:57 by ckappe            #+#    #+#             */
/*   Updated: 2025/05/03 19:28:01 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef	struct s_philo
{
	pthread_t	thread;
	int		num_of_philo;
	long 	time_to_die;
	long 	time_to_eat;
	long 	time_to_sleep;
	long 	min_meals;
}				t_philo;

void 	init_data(int ac, const char **av);
t_philo init_philo(int ac, const char **av);

#endif
