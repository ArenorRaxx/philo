/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:50:19 by mcorso            #+#    #+#             */
/*   Updated: 2022/08/01 11:56:55by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <unistd.h>

int	philo_sleeps_action(t_philo *philo, int time_to_sleep)
{
	if (philo->globvar->terminate == TERMINATE)
		return (TERMINATE);
	print_action_log(philo, SLEEPS_MSG);
	usleep(time_to_sleep * ONE_MS);
	return (philo->globvar->terminate);
}
