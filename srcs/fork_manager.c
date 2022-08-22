/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:48:43 by mcorso            #+#    #+#             */
/*   Updated: 2022/08/22 12:51:37 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <bits/pthreadtypes.h>
#include <stddef.h>

static int	malloc_forks(pthread_mutex_t **forks, int nb_of_forks)
{
	int				errnum;
	size_t			size_to_malloc;

	size_to_malloc = sizeof(**forks) * nb_of_forks;
	*forks = malloc(size_to_malloc);
	if (!*forks)
		return (ENOMEM);
	return (SUCCESS);
}

static int	init_mutex_of_forks(pthread_mutex_t *forks, int nb_of_forks)
{
	int	errnum;

	errnum = init_multiple_mutexes(nb_of_forks, forks);
	if (errnum)
		return (errnum);
	return (SUCCESS);
}

int	init_fork_objects(pthread_mutex_t *forks, int nb_of_forks)
{
	int				errnum;

	errnum = malloc_forks(&forks, nb_of_forks);
	if (errnum != SUCCESS)
		return (errnum);
	errnum = init_mutex_of_forks(forks, nb_of_forks);
	if (errnum != SUCCESS)
		return (errnum);
	return (SUCCESS);
}
