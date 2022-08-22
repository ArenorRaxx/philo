/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:58:08 by mcorso            #+#    #+#             */
/*   Updated: 2022/08/20 12:33:00 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	check_for_dead_philo(t_philo *philo, t_global *glo)
{
	int			time_to_die;
	long long	current_timestamp;
	long long	last_meal_timestamp;
	long long	time_since_philo_ate;

	time_to_die = glo->args.time_to_die;
	current_timestamp = get_timestamp();
	last_meal_timestamp = philo->last_meal;
	time_since_philo_ate = time_diff(last_meal_timestamp, current_timestamp);
	if (time_since_philo_ate > time_to_die)
		return (1);
	return (0);
}

int	test_for_death(t_philo *philo)
{
	t_global	*glo;
	int			philo_dead;

	glo = philo->globvar;
	philo_dead = check_for_dead_philo(philo, glo);
	if (philo_dead)
	{
		glo->is_ded = 1;
		print_action_log(philo, DIES_MSG);
	}
	return (glo->is_ded);
}
