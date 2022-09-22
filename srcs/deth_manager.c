/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deth_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:58:08 by mcorso            #+#    #+#             */
/*   Updated: 2022/09/22 15:20:35 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	philo_dies_action(t_philo *philo)
{
	print_action_log(philo, DIES_MSG);
}

static int	check_for_ded_philo(t_philo philo, t_global glo)
{
	int			time_to_die;
	long long	current_timestamp;
	long long	last_meal_timestamp;
	long long	time_since_philo_ate;

	time_to_die = glo.args.time_to_die;
	current_timestamp = get_timestamp();
	pthread_mutex_lock(&philo.data_access);
	last_meal_timestamp = philo.last_meal;
	time_since_philo_ate = time_diff(last_meal_timestamp, current_timestamp);
	pthread_mutex_unlock(&philo.data_access);
	if (time_since_philo_ate > time_to_die)
		return (DED);
	return (NOT_DED);
}

void	deth_manager(t_global *glo, int nb_of_philo_to_test, t_philo *philos)
{
	int				philo_is_ded;
	t_philo			current_philo;
	static int		i = 0;

	current_philo = philos[i];
	philo_is_ded = check_for_ded_philo(current_philo, *glo);
	if (philo_is_ded == DED)
	{
		glo->is_ded = 1;
		philo_dies_action(&current_philo);
	}
	if (++i == nb_of_philo_to_test)
	{
		i = 0;
		sleep_logic(8);
	}
}
