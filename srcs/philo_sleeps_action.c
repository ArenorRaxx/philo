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

void	sleep_logic(int sleep_time)
{
	usleep(sleep_time * 1000);
}

int	philo_sleeps_action(t_philo *philo, int time_to_sleep)
{
	philo->state = 2;
	if (philo->globvar->is_ded == DED)
		return (DED);
	print_action_log(philo, SLEEPS_MSG);
	sleep_logic(time_to_sleep);
	return (philo->globvar->is_ded);
}
