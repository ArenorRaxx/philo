/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 10:34:41 by mcorso            #+#    #+#             */
/*   Updated: 2022/04/14 08:16:02 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <bits/types/struct_timeval.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

struct	s_global;

/*			PARSING & ARGS		*/
typedef struct s_args {
	int	nb_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_time_eats;
}				t_args;

int			ft_atoi(char *nbr);
int			check_args(int argc, char **argv);
int			manage_glob(struct s_global *glo, int argc, char **argv);

/*			GENERAL & PHILOS	*/
typedef struct s_philo {
	int				id;
	long long		last_meal;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_global	*globvar;
}				t_philo;

typedef struct s_global {
	struct s_args	args;
	pthread_mutex_t	*write;
	pthread_mutex_t	*forks;
	long long		time_ref;
	t_philo			*philos;

}				t_global;

int			philo_manager(t_global *glo);

inline static int	malloc_forks(t_philo *philo)
{
	philo->left_fork = (pthread_mutex_t *)malloc(sizeof(*philo->left_fork));
	philo->right_fork = (pthread_mutex_t *)malloc(sizeof(*philo->right_fork));
	if (!philo->left_fork || !philo->right_fork)
		return (-1);
	return (0);
}

/*			TIME MANAGEMENT		*/
void		print_log(t_global glo, int id, char *action);
long long	get_timestamp(void);
long long	time_diff(long long t1, long long t2);

#endif