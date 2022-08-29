/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 10:40:14 by mcorso            #+#    #+#             */
/*   Updated: 2022/08/29 11:43:58 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int			i;
	int			error;
	t_global	glo;

	i = 0;
	error = catch_parsing_and_glo_error(&glo, argc, argv);
	if (error != SUCCESS)
		return (print_error_and_return(error));
	error = catch_philo_init_and_threading_error(&glo);
	if (error)
		return (print_error_and_return(error));
	while (glo.is_ded == NOT_DED)
		deth_manager(&glo);
	while (i < glo.args.nb_philosophers)
		pthread_join(glo.philos[i++].thread_id, NULL);
	return (0);
}
