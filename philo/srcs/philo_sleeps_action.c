/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleeps_action.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:50:19 by mcorso            #+#    #+#             */
/*   Updated: 2022/10/15 13:15:24 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <unistd.h>

void	philo_sleeps_action(int philo_id, t_global *glo, int time_to_sleep)
{
	print_action_log(philo_id, glo, SLEEPS_MSG);
	usleep(time_to_sleep * ONE_MS);
}
