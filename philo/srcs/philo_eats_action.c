/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eats_action.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:09:59 by mcorso            #+#    #+#             */
/*   Updated: 2022/10/10 19:05:47 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static void	update_philo_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_access);
	philo->last_meal = get_timestamp();
	pthread_mutex_unlock(&philo->data_access);
}

static void	philo_takes_forks_action(t_philo *philo)
{
	int				i;
	pthread_mutex_t	*forks[NB_FORK_PER_PHILO];

	i = 0;
	forks[FIRST_FORK] = philo->first_fork;
	forks[SECOND_FORK] = philo->second_fork;
	while (i < NB_FORK_PER_PHILO)
	{
		pthread_mutex_lock(forks[i++]);
		if (!philo->globvar->terminate)
			print_action_log(philo, TAKES_FORK_MSG);
	}
}

static void	philo_drops_forks(t_philo *philo)
{
	int				i;
	pthread_mutex_t	*forks[NB_FORK_PER_PHILO];

	i = 0;
	forks[FIRST_FORK] = philo->first_fork;
	forks[SECOND_FORK] = philo->second_fork;
	while (i < NB_FORK_PER_PHILO)
		pthread_mutex_unlock(forks[i++]);
}

void	philo_eats_action(t_philo *philo, const int time_to_eat)
{
	const t_global	*glo = philo->globvar;

	philo_takes_forks_action(philo);
	if (!glo->terminate)
	{
		print_action_log(philo, EATS_MSG);
		update_philo_last_meal(philo);
		usleep(time_to_eat * ONE_MS);
		philo->nb_of_meal++;
	}
	philo_drops_forks(philo);
}
