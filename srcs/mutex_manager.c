/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 10:57:15 by mcorso            #+#    #+#             */
/*   Updated: 2022/08/22 12:37:56 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdlib.h>

int	init_single_mutex(pthread_mutex_t mutex)
{
	int	errnum;

	errnum = pthread_mutex_init(&mutex, NULL);
	if (errnum != SUCCESS)
		return (errnum);
	return (SUCCESS);
}

int	init_multiple_mutexes(int nb_of_mutexes, pthread_mutex_t *mutex_array)
{
	int				i;
	int				errnum;

	i = 0;
	errnum = 0;
	while (i < nb_of_mutexes)
	{
		errnum = init_single_mutex(mutex_array[i]);
		if (errnum != SUCCESS)
			return (errnum);
		i++;
	}
	return (SUCCESS);
}

int	init_mutex_objects_of_glo(t_global *glo)
{
	int				errnum;
	int				nb_of_forks;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex_object;

	nb_of_forks = glo->args.nb_philosophers;
	forks = glo->forks;
	errnum = init_fork_objects(forks, nb_of_forks);
	if (errnum != SUCCESS)
		return (errnum);
	write_mutex_object = glo->write;
	errnum = init_single_mutex(write_mutex_object);
	if (errnum != SUCCESS)
		return (errnum);
	return (SUCCESS);
}
