/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 19:45:04 by mcorso            #+#    #+#             */
/*   Updated: 2022/08/22 12:27:48 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>

long long	get_timestamp(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long long	time_diff(long long t1, long long t2)
{
	return (t2 - t1);
}

void	print_action_log(t_philo *philo, char *action)
{
	const t_global	glo = *philo->globvar;
	const int		philo_id = philo->id;
	long long		time_difference;
	long long		time_at_t;
	pthread_mutex_t	write;

	write = glo.write;
	time_at_t = get_timestamp();
	time_difference = time_diff(glo.time_ref, time_at_t);
	pthread_mutex_lock(&write);
	printf("%lli ", time_difference);
	printf("%i ", philo_id);
	printf("%s\n", action);
	pthread_mutex_unlock(&write);
	return ;
}
