/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eats_action.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:09:59 by mcorso            #+#    #+#             */
/*   Updated: 2022/09/26 18:01:13 by mcorso           ###   ########.fr       */
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
		if (philo->globvar->is_ded == DED)
		{
			pthread_mutex_unlock(forks[0]);
			if (i == 1)
				pthread_mutex_unlock(forks[1]);
			return (DED);
		}
		print_action_log(philo, TAKES_FORK_MSG);
		i++;
	}
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

	philo->state = 1;
	errnum = philo_takes_forks_action(philo);
	if (errnum != SUCCESS)
		return (errnum);
	if (glo->is_ded == DED)
	{
		philo_drops_forks(philo);
		return (DED);
	}
	print_action_log(philo, EATS_MSG);
	errnum = update_philo_last_meal(philo);
	if (errnum != SUCCESS)
		return (errnum);
	sleep_logic(time_to_eat);
	errnum = philo_drops_forks(philo);
	return (errnum);
}
