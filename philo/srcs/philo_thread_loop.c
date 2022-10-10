/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread_loop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:03:11 by mcorso            #+#    #+#             */
/*   Updated: 2022/10/05 15:10:54 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	synchroneous_start(pthread_mutex_t *start)
{
	pthread_mutex_lock(start);
	pthread_mutex_unlock(start);
}

void	*philo_in_a_thread(void *arg)
{
	t_philo		*philo;
	t_global	*glo;
	int			time_to_eat;
	int			time_to_sleep;

	philo = (t_philo *)arg;
	glo = philo->globvar;
	time_to_eat = glo->args.time_to_eat;
	time_to_sleep = glo->args.time_to_sleep;
	synchroneous_start(&glo->start);
	if (philo->id % 2 == 0)
		usleep((time_to_eat * ONE_MS) / 2);
	while (!glo->terminate)
	{
		if (!glo->terminate)
			philo_eats_action(philo, time_to_eat);
		if (!glo->terminate)
			philo_sleeps_action(philo, time_to_sleep);
		if (!glo->terminate)
			print_action_log(philo, THINKS_MSG);
	}
	return (NULL);
}
