/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:32:50 by mcorso            #+#    #+#             */
/*   Updated: 2022/04/14 08:24:59 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	init_glob(t_global *glo, int argc, char **argv)
{
	glo->args.nb_philosophers = ft_atoi(argv[1]);
	glo->args.time_to_die = ft_atoi(argv[2]);
	glo->args.time_to_eat = ft_atoi(argv[3]);
	glo->args.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		glo->args.nb_time_eats = -1;
	else
		glo->args.nb_time_eats = ft_atoi(argv[5]);
	glo->forks = malloc(sizeof(*glo->forks) * glo->args.nb_philosophers);
	glo->write = malloc(sizeof(*glo->write));
	if (!glo->forks || !glo->write)
		return (-1);
	glo->time_ref = get_timestamp();
	return (0);
}

int	manage_glob(t_global *glo, int argc, char **argv)
{
	if (check_args(argc, argv) < 0)
	{
		printf("Error in parsing\n");
		return (-1);
	}
	if (init_glob(glo, argc, argv) < 0)
	{
		printf("Sorry. Malloc error.");
		return (-1);
	}
	return (0);
}
