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
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <sys/time.h>

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

static int	create_and_synchro_lock_threads(int nb_of_philos, t_philo **philos)
{
	int	i;
	int	errnum;

	i = 0;
	while (i < nb_of_philos)
	{
		errnum = pthread_create(&(*philos)[i].thread_id, NULL, \
								philo_in_a_thread, &(*philos)[i]);
		if (errnum != SUCCESS)
			return (errnum);
		errnum = pthread_mutex_lock(&(*philos)[i].data_access);
		if (errnum != SUCCESS)
			return (errnum);
		i++;
	}
	return (SUCCESS);
}

static int	unlock_synchro_threads(int nb_of_philos, t_philo **philos)
{
	int	i;
	int	errnum;

	i = 0;
	while (i < nb_of_philos)
	{
		errnum = pthread_mutex_unlock(&philos[i]->data_access);
		if (errnum != SUCCESS)
			return (errnum);
		i++;
	}
	return (SUCCESS);
}

static int	catch_synchroneous_thread_creation_error(t_global *glo)
{
	int		errnum;
	int		nb_of_philos;
	t_philo	*philos;

	nb_of_philos = glo->args.nb_philosophers;
	philos = glo->philos;
	errnum = create_and_synchro_lock_threads(nb_of_philos, &philos);
	if (errnum != SUCCESS)
		return (errnum);
	errnum = unlock_synchro_threads(nb_of_philos, &philos);
	if (errnum != SUCCESS)
		return (errnum);
	return (SUCCESS);
}

int	catch_philo_init_and_threading_error(t_global *glo)
{
	int		errnum;

	errnum = init_global_philo(glo);
	if (errnum != SUCCESS)
		return (errnum);
	errnum = catch_synchroneous_thread_creation_error(glo);
	if (errnum != SUCCESS)
		return (errnum);
	return (SUCCESS);
}
