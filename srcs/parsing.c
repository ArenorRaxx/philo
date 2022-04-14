/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:27:04 by mcorso            #+#    #+#             */
/*   Updated: 2022/04/13 09:46:18 by mcorso           ###   ########.fr       */
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

int	check_args(int argc, char **argv)
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

int	ft_atoi(char *nbr)
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
