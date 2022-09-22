/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 10:40:14 by mcorso            #+#    #+#             */
/*   Updated: 2022/09/22 15:06:55 by mcorso           ###   ########.fr       */
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

	error = catch_parsing_and_glo_error(glo, argc, argv);
	if (error != SUCCESS)
		return (print_error_and_return(error));
	error = catch_philo_init_and_threading_error(glo);
	return (print_error_and_return(error));
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
	return (SUCCESS);
}
