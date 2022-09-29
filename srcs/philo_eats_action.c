/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eats_action.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:09:59 by mcorso            #+#    #+#             */
/*   Updated: 2022/09/29 15:36:57 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static int	update_philo_last_meal(t_philo *philo)
{
	int	error;

	error = pthread_mutex_lock(&philo->data_access);
	if (error != SUCCESS)
		return (error);
	philo->last_meal = get_timestamp();
	error = pthread_mutex_unlock(&philo->data_access);
	return (error);
}

static int	philo_takes_forks_action(t_philo *philo)
{
	int				i;
	int				errnum;
	pthread_mutex_t	*forks[NB_FORK_PER_PHILO];

	i = 0;
	forks[LEFT_FORK] = philo->left_fork;
	forks[RIGHT_FORK] = philo->right_fork;
	while (i < NB_FORK_PER_PHILO)
	{
		errnum = pthread_mutex_lock(forks[i]);
		if (errnum != SUCCESS)
			return (errnum);
		if (philo->globvar->terminate == TERMINATE)
		{
			pthread_mutex_unlock(forks[0]);
			if (i == 1)
				pthread_mutex_unlock(forks[1]);
			return (TERMINATE);
		}
		i++;
	}
	while (i-- >= 0)
		print_action_log(philo, TAKES_FORK_MSG);
	return (SUCCESS);
}

static int	philo_drops_forks(t_philo *philo)
{
	int				i;
	int				errnum;
	pthread_mutex_t	*forks[NB_FORK_PER_PHILO];

	i = 0;
	forks[LEFT_FORK] = philo->left_fork;
	forks[RIGHT_FORK] = philo->right_fork;
	while (i < NB_FORK_PER_PHILO)
	{
		errnum = pthread_mutex_unlock(forks[i]);
		if (errnum != SUCCESS)
			break ;
		i++;
	}
	return (errnum);
}

int	philo_eats_action(t_philo *philo)
{
	int				errnum;
	const t_global	*glo = philo->globvar;
	const int		time_to_eat = glo->args.time_to_eat;

	errnum = philo_takes_forks_action(philo);
	if (errnum != SUCCESS)
		return (errnum);
	if (glo->terminate == TERMINATE)
	{
		philo_drops_forks(philo);
		return (TERMINATE);
	}
	print_action_log(philo, EATS_MSG);
	errnum = update_philo_last_meal(philo);
	if (errnum != SUCCESS)
		return (errnum);
	usleep(time_to_eat * ONE_MS);
	philo->nb_of_meal++;
	errnum = philo_drops_forks(philo);
	if (philo->nb_of_meal == philo->globvar->args.nb_time_eats)
		return (TERMINATE);
	return (errnum);
}
