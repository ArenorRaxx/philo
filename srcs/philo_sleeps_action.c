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

int	sleep_logic(t_philo *philo, int sleep_time)
{
	while (sleep_time--)
	{
		usleep(1000);
		if (philo->globvar->is_ded == 1)
			return (DED);
	}
	return (NOT_DED);
}

int	philo_sleeps_action(t_philo *philo, int time_to_sleep)
{
	int	sleep_return;

	print_action_log(philo, SLEEPS_MSG);
	sleep_return = sleep_logic(philo, time_to_sleep);
	return (sleep_return);
}
