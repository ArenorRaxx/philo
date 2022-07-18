/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:32:50 by mcorso            #+#    #+#             */
/*   Updated: 2022/07/18 15:54:19 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	check_number(char *arg)
{
	int	i;
	int	nb;
	int	curr_nb;

	i = 0;
	nb = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (-1);
		nb *= 10;
		curr_nb = arg[i] - '0';
		if (nb + curr_nb - curr_nb != nb)
			return (-1);
		nb += curr_nb;
		i++;
	}
	return (0);
}

static int	check_args(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (-1);
	while (++i < argc)
		if (check_number(argv[i]))
			return (-1);
	return (0);
}

static int	ft_atoi(char *nbr)
{
	int	i;
	int	retnbr;

	i = 0;
	retnbr = 0;
	while (nbr[i] && nbr)
	{
		retnbr *= 10;
		retnbr += nbr[i] - '0';
		i++;
	}
	return (retnbr);
}

static int	fill_glo(t_global *glo, int argc, char **argv)
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

int	parse_args_and_fill_glo(t_global *glo, int nb_args, char **args)
{
	if (check_args(nb_args, args) < 0)
		return (print_error_and_return("Error in parsing"));
	if (fill_glo(glo, nb_args, args) < 0)
		return (print_error_and_return("Malloc error"));
	return (0);
}
