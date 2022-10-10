/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termination_manager.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:58:08 by mcorso            #+#    #+#             */
/*   Updated: 2022/10/10 19:33:18 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <unistd.h>

static void	philo_dies_action(t_philo *philo)
{
	print_action_log(philo, DIES_MSG);
}

static int	check_for_ded_philo(t_philo philo, t_global glo)
{
	const long long	current_timestamp = get_timestamp();
	const int		time_to_die = glo.args.time_to_die;
	long long		last_meal_timestamp;
	long long		time_since_philo_ate;

	pthread_mutex_lock(&philo.data_access);
	last_meal_timestamp = philo.last_meal;
	pthread_mutex_unlock(&philo.data_access);
	time_since_philo_ate = time_diff(last_meal_timestamp, current_timestamp);
	return (time_since_philo_ate > time_to_die);
}

static void	deth_manager(t_global *glo, t_philo current_philo)
{
	int				philo_is_ded;

	philo_is_ded = check_for_ded_philo(current_philo, *glo);
	if (philo_is_ded == DED)
	{
		glo->terminate = 1;
		philo_dies_action(&current_philo);
	}
}

static void	ration_manager(	t_global *glo, int nb_of_philo_to_test, \
							t_philo current_philo)
{
	const int	philo_id = current_philo.id;
	const int	nb_of_meal_to_have = glo->args.nb_time_eats;
	static int	nb_of_philo_that_ate_enough = 0;
	static int	has_philosopher_i_enough_meal[200];

	if (!has_philosopher_i_enough_meal[philo_id] && \
		current_philo.nb_of_meal >= nb_of_meal_to_have)
	{
		has_philosopher_i_enough_meal[philo_id]++;
		nb_of_philo_that_ate_enough++;
	}

	if (nb_of_philo_that_ate_enough == nb_of_philo_to_test)
	{
		glo->terminate = 1;
		print_end_by_ration(glo);
	}
}

void	termination_manager(t_global *glo)
{
	int			nb_of_philo;
	t_philo		current_philo;
	static int	i = 0;

	current_philo = glo->philos[i];
	nb_of_philo = glo->args.nb_philosophers;
	if (glo->args.nb_time_eats >= 0)
		ration_manager(glo, nb_of_philo, current_philo);
	deth_manager(glo, current_philo);
	if (++i == nb_of_philo)
		usleep(8 * ONE_MS);
	i *= (i != nb_of_philo);
}
