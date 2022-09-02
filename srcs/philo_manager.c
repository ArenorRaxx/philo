/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 12:17:15 by mcorso            #+#    #+#             */
/*   Updated: 2022/04/13 10:03:06y mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>
#include <sys/time.h>

static t_philo	init_single_philo(int index, int number_of_philo, t_global *glo)
{
	t_philo	philosopher;

	philosopher.id = index + 1;
	philosopher.globvar = glo;
	philosopher.last_meal = get_timestamp();
	philosopher.left_fork = &glo->forks[index];
	if (index == number_of_philo - 1)
		philosopher.right_fork = &glo->forks[0];
	else
		philosopher.right_fork = &glo->forks[index + 1];
	return (philosopher);
}

static int	init_global_philo(t_global *glo)
{
	int		i;
	int		number_of_philo;
	t_philo	current_init_philo;

	i = 0;
	number_of_philo = glo->args.nb_philosophers;
	glo->philos = malloc(sizeof(*glo->philos) * number_of_philo);
	if (!glo->philos)
		return (ENOMEM);
	while (i < number_of_philo)
	{
		current_init_philo = init_single_philo(i, number_of_philo, glo);
		glo->philos[i] = current_init_philo;
		i++;
	}
	return (SUCCESS);
}

static void	*philo_in_a_thread(void *arg)
{
	t_global	*glo;
	t_philo		*philo;
	int			time_to_sleep;

	philo = (t_philo *)arg;
	glo = philo->globvar;
	time_to_sleep = glo->args.time_to_sleep;
	while (!glo->is_ded)
	{
		if (philo_eats_action(philo) == DED)
			break ;
		if (philo_sleeps_action(philo, time_to_sleep) == DED)
			break ;
		philo_thinks_action(philo);
	}
	return (NULL);
}

int	catch_philo_init_and_threading_error(t_global *glo)
{
	int		i;
	int		errnum;
	t_philo	*philos;

	i = 0;
	errnum = init_global_philo(glo);
	if (errnum != SUCCESS)
		return (errnum);
	philos = glo->philos;
	while (i < glo->args.nb_philosophers)
	{
		errnum = pthread_create(&philos[i].thread_id, NULL, \
								philo_in_a_thread, &philos[i]);
		if (errnum != SUCCESS)
			return (errnum);
		i++;
	}
	return (SUCCESS);
}
