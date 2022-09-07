/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 10:40:14 by mcorso            #+#    #+#             */
/*   Updated: 2022/09/07 12:15:56 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int				i;
	int				error;
	t_global		glo;
	pthread_mutex_t	starter;

	i = 0;
	while (1)
	{
		error = catch_parsing_and_glo_error(&glo, argc, argv);
		if (error != SUCCESS)
			break ;
		starter = glo.starter;
		pthread_mutex_lock(&starter);
		error = catch_philo_init_and_threading_error(&glo);
		if (error != SUCCESS)
			break ;
		pthread_mutex_unlock(&starter);
		while (glo.is_ded == NOT_DED)
			deth_manager(&glo);
		while (i < glo.args.nb_philosophers)
			pthread_join(glo.philos[i++].thread_id, NULL);
		break ;
	}
	if (error != SUCCESS)
		return (print_error_and_return(error));
	return (0);
}
