/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eats_action.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:09:59 by mcorso            #+#    #+#             */
/*   Updated: 2022/08/24 15:37:57 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>

static int	philo_takes_single_fork(pthread_mutex_t *fork)
{
	int	errnum;

	errnum = pthread_mutex_lock(fork);
	if (errnum != SUCCESS)
		return (errnum);
	return (SUCCESS);
}

static int	philo_drops_single_fork(pthread_mutex_t *fork)
{
	int	errnum;

	errnum = pthread_mutex_unlock(fork);
	if (errnum != SUCCESS)
		return (errnum);
	return (SUCCESS);
}

static int	philo_takes_forks_action(t_philo *philo)
{
	int				i;
	int				errnum;
	pthread_mutex_t	forks[NB_FORK_PER_PHILO];

	i = 0;
	forks[LEFT_FORK] = *philo->left_fork;
	forks[RIGHT_FORK] = *philo->right_fork;
	while (i < NB_FORK_PER_PHILO)
	{
		errnum = philo_takes_single_fork(&forks[i]);
		if (errnum != SUCCESS)
			return (errnum);
		print_action_log(philo, TAKES_FORK_MSG);
		i++;
	}
	return (SUCCESS);
}

static int	philo_drops_forks(t_philo *philo)
{
	int				i;
	int				errnum;
	pthread_mutex_t	forks[NB_FORK_PER_PHILO];

	i = 0;
	forks[LEFT_FORK] = *philo->left_fork;
	forks[RIGHT_FORK] = *philo->right_fork;
	while (i < NB_FORK_PER_PHILO)
	{
		errnum = philo_drops_single_fork(&forks[i]);
		if (errnum != SUCCESS)
			return (errnum);
		i++;
	}
	return (SUCCESS);
}

int	philo_eats_action(t_philo *philo)
{
	int				errnum;
	const t_global	*glo = philo->globvar;
	const int		time_to_eat = glo->args.time_to_eat;

	errnum = philo_takes_forks_action(philo);
	if (errnum != SUCCESS)
		return (errnum);
	print_action_log(philo, EATS_MSG);
	philo->last_meal = get_timestamp();
	sleep_logic(philo, time_to_eat);
	errnum = philo_drops_forks(philo);
	if (errnum != SUCCESS)
		return (errnum);
	return (SUCCESS);
}
