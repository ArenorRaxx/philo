/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thinks_action.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:29:29 by mcorso            #+#    #+#             */
/*   Updated: 2022/08/22 13:32:40 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_thinks_action(t_philo *philo)
{
	print_action_log(philo, THINKS_MSG);
}