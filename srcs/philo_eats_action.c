/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eats_action.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:09:59 by mcorso            #+#    #+#             */
/*   Updated: 2022/08/22 10:04:57 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>

static void	philo_takes_single_fork(pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	return ;
}

static void	philo_drops_single_fork(pthread_mutex_t *fork)
{
	pthread_mutex_unlock(fork);
	return ;
}

static int	philo_takes_forks_action(t_philo *philo)
{
	int				i;
	pthread_mutex_t	forks[NB_FORK_PER_PHILO];

	i = 0;
	forks[LEFT_FORK] = *philo->left_fork;
	forks[RIGHT_FORK] = *philo->right_fork;
	while (i < NB_FORK_PER_PHILO)
	{
		philo_takes_single_fork(&forks[i]);
		print_action_log(philo, TAKES_FORK_MSG);
		i++;
	}
	return (0);
}

static void	philo_drops_forks(t_philo *philo)
{
	int				i;
	pthread_mutex_t	forks[NB_FORK_PER_PHILO];

	i = 0;
	forks[LEFT_FORK] = *philo->left_fork;
	forks[RIGHT_FORK] = *philo->right_fork;
	while (i < NB_FORK_PER_PHILO)
	{
		philo_drops_single_fork(&forks[i]);
		i++;
	}
	return ;
}

int	philo_eats_action(t_philo *philo)
{
	const t_global	*glo = philo->globvar;
	const int		time_to_eat = glo->args.time_to_eat;

	philo_takes_forks_action(philo);
	print_action_log(philo, EATS_MSG);
	philo->last_meal = get_timestamp();
	sleep_logic(philo, time_to_eat);
	philo_drops_forks(philo);
	return ;
}
