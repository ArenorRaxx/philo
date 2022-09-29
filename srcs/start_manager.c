/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:58:15 by mcorso            #+#    #+#             */
/*   Updated: 2022/09/29 15:24:00 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	malloc_start(pthread_mutex_t **start, int nb_of_philo_to_start)
{
	size_t	size_to_malloc;

	size_to_malloc = nb_of_philo_to_start * sizeof(**start);
	*start = malloc(size_to_malloc);
	if (!*start)
		return (ENOMEM);
	return (SUCCESS);
}

static int	init_mutex_of_start(pthread_mutex_t **start, \
								int nb_of_philo_to_start)
{
	int	errnum;

	errnum = init_multiple_mutexes(nb_of_philo_to_start, start);
	return (errnum);
}

void	free_start(pthread_mutex_t **start)
{
	free(*start);
}

int	init_start_objects(pthread_mutex_t **start, int nb_of_philo_to_start)
{
	int	errnum;

	errnum = malloc_start(start, nb_of_philo_to_start);
	if (errnum != SUCCESS)
		return (errnum);
	errnum = init_mutex_of_start(start, nb_of_philo_to_start);
	return (errnum);
}
