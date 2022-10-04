/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread_loop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:03:11 by mcorso            #+#    #+#             */
/*   Updated: 2022/10/04 14:57:43 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	synchroneous_start(t_philo *philo)
{
	pthread_mutex_lock(philo->start);
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
	synchroneous_start(philo);
	if (philo->id % 2 == 0)
		usleep(1000);
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
