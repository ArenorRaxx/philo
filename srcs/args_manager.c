/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:32:50 by mcorso            #+#    #+#             */
/*   Updated: 2022/09/29 14:35:58 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
			return (ENAN);
		nb *= 10;
		curr_nb = arg[i] - '0';
		if (nb + curr_nb - curr_nb != nb)
			return (EMAXINT);
		nb += curr_nb;
		i++;
	}
	return (SUCCESS);
}

static int	check_args_validity(int argc, char **argv)
{
	int	i;
	int	errnum;

	i = 0;
	if (argc != 5 && argc != 6)
		return (EINBARG);
	while (++i < argc)
	{
		errnum = check_number(argv[i]);
		if (errnum != SUCCESS)
			break ;
	}
	return (errnum);
}

static int	fill_glo_variable(t_global *glo, int argc, char **argv)
{
	int	errnum;

	glo->args.nb_philosophers = ft_atoi(argv[1]);
	glo->args.time_to_die = ft_atoi(argv[2]);
	glo->args.time_to_eat = ft_atoi(argv[3]);
	glo->args.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		glo->args.nb_time_eats = -1;
	else
		glo->args.nb_time_eats = ft_atoi(argv[5]);
	errnum = init_mutex_objects_of_glo(glo);
	if (errnum != SUCCESS)
		return (errnum);
	glo->is_ded = 0;
	glo->terminate = 0;
	return (SUCCESS);
}

int	catch_parsing_and_glo_error(t_global *glo, int nb_args, char **args)
{
	int	errnum;

	errnum = check_args_validity(nb_args, args);
	if (errnum != SUCCESS)
		return (errnum);
	errnum = fill_glo_variable(glo, nb_args, args);
	return (errnum);
}
