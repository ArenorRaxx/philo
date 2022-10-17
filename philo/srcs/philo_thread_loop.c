/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread_loop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:03:11 by mcorso            #+#    #+#             */
/*   Updated: 2022/10/15 13:19:47 by mcorso           ###   ########.fr       */
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
	int			id;
	int			time_to_eat;
	int			time_to_sleep;

	philo = (t_philo *)arg;
	glo = philo->globvar;
	id = philo->id;
	time_to_eat = glo->args.time_to_eat;
	time_to_sleep = glo->args.time_to_sleep;
	synchroneous_start(&glo->start);
	if (id % 2 == 0)
		usleep((time_to_eat * ONE_MS) / 2);
	while (get_terminate_var(glo) != TERMINATE)
	{
		philo_eats_action(philo, glo, time_to_eat);
		philo_sleeps_action(id, glo, time_to_sleep);
		print_action_log(id, glo, THINKS_MSG);
	}
	return (NULL);
}
