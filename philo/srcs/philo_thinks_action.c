/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thinks_action.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:22:30 by mcorso            #+#    #+#             */
/*   Updated: 2022/10/17 16:35:52 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_thinks_action(int philo_id, t_global *glo)
{
	print_action_log(philo_id, glo, THINKS_MSG);
	if (glo->args.nb_philosophers % 2 == 1)
		usleep((glo->args.time_to_eat - 10) * ONE_MS);
}
