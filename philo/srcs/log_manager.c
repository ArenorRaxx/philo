/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 19:45:04 by mcorso            #+#    #+#             */
/*   Updated: 2022/10/14 14:30:35 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>

static long long	read_time_ref(t_global *glo)
{
	long long		time_ref;

	pthread_mutex_lock(&glo->data_access);
	time_ref = glo->time_ref;
	pthread_mutex_unlock(&glo->data_access);
	return (time_ref);
}

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
	t_global				*glo;
	pthread_mutex_t			write;
	const int				philo_id = philo->id;
	long long				delta_time_since_start;
	long long				time_ref;

	glo = philo->globvar;
	write = glo->write;
	time_ref = read_time_ref(glo);
	delta_time_since_start = time_diff(time_ref, get_timestamp());
	pthread_mutex_lock(&write);
	printf("%lli %i %s\n", delta_time_since_start, philo_id, action);
	pthread_mutex_unlock(&write);
}
