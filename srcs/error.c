/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:12:54 by mcorso            #+#    #+#             */
/*   Updated: 2022/09/22 15:06:34 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>

static void	print_error(const char *error_msg)
{
	printf("%s\n", error_msg);
}

static void	print_args_error(int errnum)
{
	print_error(PARSING_ERROR_MSG);
	if (errnum == ENAN)
		print_error(ENAN_MSG);
	else if (errnum == EMAXINT)
		print_error(EMAXINT_MSG);
	else if (errnum == EINBARG)
		print_error(EINBARG_MSG);
}

static void	print_general_error(int errnum)
{
	if (errnum == ENOMEM)
		print_error(ENOMEM_MSG);
	else if (errnum == EINVAL)
		print_error(EINVAL_MSG);
}

int	print_error_and_return(int errnum)
{
	if (errnum == SUCCESS)
		return (SUCCESS);
	else if (errnum < 0)
		print_args_error(errnum);
	else
		print_general_error(errnum);
	return (-1);
}
