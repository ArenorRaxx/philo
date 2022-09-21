/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 10:40:14 by mcorso            #+#    #+#             */
/*   Updated: 2022/09/21 15:42:20 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static int	launch_philo_project(t_global *glo, int argc, char **argv)
{
	int				error;
	pthread_mutex_t	starter;

	error = catch_parsing_and_glo_error(glo, argc, argv);
	if (error != SUCCESS)
		return (print_error_and_return(error));
	starter = glo->starter;
	pthread_mutex_lock(&starter);
	error = catch_philo_init_and_threading_error(glo);
	if (error != SUCCESS)
		return (print_error_and_return(error));
	pthread_mutex_unlock(&starter);
	return (0);
}

int	main(int argc, char **argv)
{
	int				i;
	t_global		glo;

	i = 0;
	if (launch_philo_project(&glo, argc, argv) != SUCCESS)
		return (-1);
	while (glo.is_ded == NOT_DED)
		deth_manager(&glo, glo.args.nb_philosophers, glo.philos);
	while (i < glo.args.nb_philosophers)
		pthread_join(glo.philos[i++].thread_id, NULL);
	free_forks(&glo.forks);
	free(glo.philos);
	return (0);
}
