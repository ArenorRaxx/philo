/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 10:40:14 by mcorso            #+#    #+#             */
/*   Updated: 2022/04/13 09:55:26 by mcorso           ###   ########.fr       */
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
	t_global	glo;

	i = 0;
	if (manage_glob(&glo, argc, argv) < 0)
		return (-1);
	if (philo_manager(&glo) < 0)
		return (-1);
	while (i < glo.args.nb_philosophers)
		pthread_join(glo.philos[i++].thread_id, NULL);
	return (0);
}
