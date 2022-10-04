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
		glo->philos[i++] = current_init_philo;
	}
	return (SUCCESS);
}

static void	create_and_synchro_lock_threads(int nb_of_philos, \
											t_philo **philos, \
											pthread_mutex_t **start)
{
	int	i;

	i = 0;
	while (i < nb_of_philos)
	{
		pthread_mutex_lock(&(*start)[i]);
		pthread_create(&(*philos)[i].thread_id, NULL, \
								philo_in_a_thread, &(*philos)[i]);
		i++;
	}
}

static void	unlock_synchro_threads(	int nb_of_philos, pthread_mutex_t **start, \
									t_philo **philos, long long time_ref)
{
	int	i;

	i = 0;
	while (i < nb_of_philos)
	{
		(*philos)[i].last_meal = time_ref;
		pthread_mutex_unlock(&(*start)[i++]);
	}
}

static void	catch_synchroneous_thread_creation_error(t_global *glo)
{
	int				nb_of_philos;
	t_philo			*philos;
	pthread_mutex_t	*start;

	nb_of_philos = glo->args.nb_philosophers;
	philos = glo->philos;
	start = glo->start;
	create_and_synchro_lock_threads(nb_of_philos, &philos, &start);
	glo->time_ref = get_timestamp();
	unlock_synchro_threads(nb_of_philos, &start, &philos, glo->time_ref);
}

int	catch_philo_init_and_threading_error(t_global *glo)
{
	int		errnum;

	errnum = init_global_philo(glo);
	if (errnum != SUCCESS)
		return (errnum);
	catch_synchroneous_thread_creation_error(glo);
	return (SUCCESS);
}
