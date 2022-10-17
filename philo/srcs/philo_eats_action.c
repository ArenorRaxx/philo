/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eats_action.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:09:59 by mcorso            #+#    #+#             */
/*   Updated: 2022/10/15 13:35:00 by mcorso           ###   ########.fr       */
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

static void	count_one_more_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_access);
	philo->nb_of_meal++;
	pthread_mutex_unlock(&philo->data_access);
}

static void	philo_takes_forks_action(t_philo *philo, t_global *glo)
{
	int				i;
	pthread_mutex_t	*forks[NB_FORK_PER_PHILO];

	i = 0;
	forks[FIRST_FORK] = philo->first_fork;
	forks[SECOND_FORK] = philo->second_fork;
	while (i < NB_FORK_PER_PHILO)
	{
		pthread_mutex_lock(forks[i++]);
		print_action_log(philo->id, glo, TAKES_FORK_MSG);
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

void	philo_eats_action(t_philo *philo, t_global *glo, int time_to_eat)
{
	if (glo->args.nb_philosophers == 1)
	{
		print_action_log(philo->id, glo, TAKES_FORK_MSG);
		usleep(glo->args.time_to_die * ONE_MS);
		return ;
	}
	philo_takes_forks_action(philo, glo);
	if (!get_terminate_var(glo))
	{
		print_action_log(philo->id, glo, EATS_MSG);
		update_philo_last_meal(philo);
		usleep(time_to_eat * ONE_MS);
		count_one_more_meal(philo);
	}
	philo_drops_forks(philo);
}
