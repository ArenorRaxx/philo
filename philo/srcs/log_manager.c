/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 19:45:04 by mcorso            #+#    #+#             */
/*   Updated: 2022/10/17 16:31:52 by mcorso           ###   ########.fr       */
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

void	print_action_log(int philo_id, t_global *glo, char *action)
{
	long long	current_time;
	long long	delta_time_since_start;
	long long	time_ref;

	current_time = get_timestamp();
	if (get_terminate_var(glo) == TERMINATE)
		return ;
	pthread_mutex_lock(&glo->data_access);
	time_ref = glo->time_ref;
	delta_time_since_start = time_diff(time_ref, current_time);
	pthread_mutex_lock(&glo->write);
	printf("%lli %i %s\n", delta_time_since_start, philo_id, action);
	pthread_mutex_unlock(&glo->write);
	pthread_mutex_unlock(&glo->data_access);
}
