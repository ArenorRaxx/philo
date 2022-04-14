/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 19:45:04 by mcorso            #+#    #+#             */
/*   Updated: 2022/04/14 08:26:17 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
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

void	print_log(t_global glo, int id, char *action)
{
	pthread_mutex_lock(glo.write);
	printf("%lli ", time_diff(glo.time_ref, get_timestamp()));
	printf("%i ", id);
	printf("%s\n", action);
	pthread_mutex_unlock(glo.write);
	return ;
}
