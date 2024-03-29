/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 10:57:15 by mcorso            #+#    #+#             */
/*   Updated: 2022/10/21 09:20:40 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdlib.h>

int	init_single_mutex(pthread_mutex_t *mutex)
{
	int	errnum;

	errnum = pthread_mutex_init(mutex, NULL);
	return (errnum);
}

static void	destroy_single_mutex(pthread_mutex_t *mutex)
{
	pthread_mutex_destroy(mutex);
}

int	init_multiple_mutexes(int nb_of_mutexes, pthread_mutex_t **mutex_array)
{
	int				i;
	int				errnum;

	i = 0;
	errnum = 0;
	while (i < nb_of_mutexes)
	{
		errnum = init_single_mutex(&(*mutex_array)[i]);
		if (errnum != SUCCESS)
			return (errnum);
		i++;
	}
	return (SUCCESS);
}

int	init_mutex_objects_of_glo(t_global *glo)
{
	int				errnum;
	int				nb_of_philo;
	pthread_mutex_t	**forks;
	pthread_mutex_t	*start;
	pthread_mutex_t	*write;

	nb_of_philo = glo->args.nb_philosophers;
	forks = &glo->forks;
	errnum = init_fork_objects(forks, nb_of_philo);
	if (errnum != SUCCESS)
		return (errnum);
	start = &glo->start;
	errnum = init_single_mutex(start);
	if (errnum != SUCCESS)
		return (errnum);
	write = &glo->write;
	errnum = init_single_mutex(write);
	if (errnum != SUCCESS)
		return (errnum);
	init_single_mutex(&glo->data_access);
	return (errnum);
}

void	destroy_mutex_objects_of_glo(t_global *glo)
{
	int				nb_of_philo;
	pthread_mutex_t	**forks;
	pthread_mutex_t	*start;
	pthread_mutex_t	*write;
	pthread_mutex_t	*data_access;

	nb_of_philo = glo->args.nb_philosophers;
	forks = &glo->forks;
	destroy_fork_objects(forks, nb_of_philo);
	start = &glo->start;
	destroy_single_mutex(start);
	write = &glo->write;
	destroy_single_mutex(write);
	data_access = &glo->data_access;
	destroy_single_mutex(data_access);
}
