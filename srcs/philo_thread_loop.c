/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread_loop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:03:11 by mcorso            #+#    #+#             */
/*   Updated: 2022/09/29 15:32:36 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	synchroneous_start(t_philo *philo)
{
	pthread_mutex_lock(philo->start);
	pthread_mutex_unlock(philo->start);
}

void	*philo_in_a_thread(void *arg)
{
	t_global		*glo;
	t_philo			*philo;
	int				time_to_sleep;

	philo = (t_philo *)arg;
	glo = philo->globvar;
	time_to_sleep = glo->args.time_to_sleep;
	synchroneous_start(philo);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!glo->terminate)
	{
		if (philo_eats_action(philo) == TERMINATE)
			break ;
		if (philo_sleeps_action(philo, time_to_sleep) == TERMINATE)
			break ;
		if (glo->terminate)
			break ;
		philo_thinks_action(philo);
	}
	return (NULL);
}
