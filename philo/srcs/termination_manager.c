/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termination_manager.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:58:08 by mcorso            #+#    #+#             */
/*   Updated: 2022/10/17 14:00:28 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <unistd.h>

static void	deth_manager(	t_global *glo, int time_to_die, \
							t_philo *current_philo)
{
	const long long	current_timestamp = get_timestamp();
	long long		last_meal_timestamp;
	long long		time_since_philo_ate;

	pthread_mutex_lock(&current_philo->data_access);
	last_meal_timestamp = current_philo->last_meal;
	time_since_philo_ate = time_diff(last_meal_timestamp, current_timestamp);
	pthread_mutex_unlock(&current_philo->data_access);
	if (time_since_philo_ate > time_to_die)
		end_by_deth_action(current_philo->id, glo);
}


static void	ration_manager(	t_global *glo, int nb_of_philo_to_test, \
							t_philo *current_philo)
{
	const int	philo_id = current_philo->id;
	const int	nb_of_meal_to_have = glo->args.nb_time_eats;
	static int	nb_of_philo_that_ate_enough = 0;
	static int	has_philosopher_i_enough_meal[200];

	pthread_mutex_lock(&current_philo->data_access);
	if (!has_philosopher_i_enough_meal[philo_id] && \
		current_philo->nb_of_meal >= nb_of_meal_to_have)
	{
		has_philosopher_i_enough_meal[philo_id]++;
		nb_of_philo_that_ate_enough++;
	}
	pthread_mutex_unlock(&current_philo->data_access);
	if (nb_of_philo_that_ate_enough == nb_of_philo_to_test)
		end_by_ration_action(glo);
}

void	termination_manager(t_global *glo)
{
	int			time_to_die;
	int			nb_of_philo;
	t_philo		*current_philo;
	static int	i = 0;

	current_philo = &glo->philos[i];
	time_to_die = glo->args.time_to_die;
	nb_of_philo = glo->args.nb_philosophers;
	if (glo->args.nb_time_eats >= 0)
		ration_manager(glo, nb_of_philo, current_philo);
	deth_manager(glo, time_to_die, current_philo);
	if (++i == nb_of_philo)
		usleep(8 * ONE_MS);
	i *= (i != nb_of_philo);
}
