/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 12:17:15 by mcorso            #+#    #+#             */
/*   Updated: 2022/04/13 10:03:06y mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>
#include <sys/time.h>

static int	init_philo(t_global *glo)
{
	int	i;

	i = 0;
	glo->philos = malloc(sizeof(*glo->philos) * glo->args.nb_philosophers);
	if (!glo->philos)
		return (-1);
	while (i < glo->args.nb_philosophers)
	{
		glo->philos[i].id = i + 1;
		glo->philos[i].globvar = glo;
		glo->philos[i].last_meal = 0;
		glo->philos[i].left_fork = &glo->forks[i];
		if (i == glo->args.nb_philosophers - 1)
			glo->philos[i].right_fork = &glo->forks[0];
		else
			glo->philos[i].right_fork = &glo->forks[i + 1];
		i++;
	}
	return (0);
}

static void	philo_eats(t_philo *philo)
{
	t_global	*glo;

	glo = philo->globvar;
	pthread_mutex_lock(philo->left_fork);
	print_log(*glo, philo->id, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_log(*glo, philo->id, "has taken a fork");
	print_log(*glo, philo->id, "is eating");
	philo->last_meal = get_timestamp();
	usleep(glo->args.time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	*philo_in_a_thread(void *arg)
{
	int			i;
	t_philo		*philo;
	t_global	*glo;

	i = 0;
	glo = philo->globvar;
	philo = (t_philo *)arg;
	while (i++ < 10)
	{
		philo_eats(philo);
		print_log(*glo, philo->id, "is sleeping");
		usleep(glo->args.time_to_sleep);
		if (philo->last_meal - get_timestamp() > glo->args.time_to_die)
			break ;
		print_log(*glo, philo->id, "is thinking");
	}
	return (NULL);
}

int	philo_manager(t_global *glo)
{
	int	i;

	i = 0;
	if (init_philo(glo) < 0)
		return (-1);
	while (i < glo->args.nb_philosophers)
	{
		if (pthread_create(&glo->philos[i].thread_id, NULL, \
			philo_in_a_thread, &glo->philos[i]) != 0)
		{
			printf("Echec de création du %i philo.\n", i - 1);
			return (-1);
		}
		i++;
	}
	return (0);
}
