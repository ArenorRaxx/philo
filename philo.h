/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 10:34:41 by mcorso            #+#    #+#             */
/*   Updated: 2022/08/31 15:51:39 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define PARSING_ERROR_MSG "Parsing error: "
# define ENAN_MSG "Negative or not a number."
# define EMAXINT_MSG "Equal or greater to max int."
# define EINBARG_MSG "Invalid number of argument."
# define EAGAIN_MSG "Not enough ressources (probably from pthread_create)."
# define ENOMEM_MSG "Not enough memory."
# define EINVAL_MSG	"Invalid argument."

/*		ERROR DEFINE			*/
//	Args
# define ENAN -3
# define EMAXINT -2
# define EINBARG -1
//	General
# define SUCCESS 0
# define EAGAIN 11
# define ENOMEM	12
# define EINVAL 22

# define LEFT_FORK 0
# define RIGHT_FORK 1
# define NB_FORK_PER_PHILO 2

# define NOT_DED 0
# define DED 1

# define DIES_MSG "is ded."
# define EATS_MSG "is eating."
# define SLEEPS_MSG "is sleeping."
# define THINKS_MSG "is thinking."
# define TAKES_FORK_MSG "has taken a fork."

# include <bits/types/struct_timeval.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

struct	s_global;

/*			STRUCTS			*/
typedef struct s_args {
	int	nb_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_time_eats;
}				t_args;

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
	pthread_mutex_t	write;
	pthread_mutex_t	*forks;
	long long		time_ref;
	t_philo			*philos;
	int				is_ded;
}				t_global;

//_______________________________
/*			INIT & PARSING		*/
int			catch_philo_init_and_threading_error(t_global *glo);
int			catch_parsing_and_glo_error(struct s_global *glo, \
										int nb_args, \
										char **args);
//	Mutexes
int			init_single_mutex(pthread_mutex_t *mutex);
int			init_multiple_mutexes(	int nb_of_mutexes, \
									pthread_mutex_t **mutex_array);
int			init_mutex_objects_of_glo(t_global *glo);
//	Forks
int			init_fork_objects(pthread_mutex_t **forks, int nb_of_forks);

//_______________________________
/*			PHILOS MANAGEMENT	*/
int			philo_manager(t_global *glo);
//	Actions
int			philo_eats_action(t_philo *philo);
int			sleep_logic(t_philo *philo, int sleep_time);
int			philo_sleeps_action(t_philo *philo, int time_to_sleep);
void		philo_thinks_action(t_philo *philo);
//	Deth
void		deth_manager(t_global *glo);

//_______________________________
/*			TIME MANAGEMENT		*/
void		print_action_log(t_philo *philo, char *action);
long long	get_timestamp(void);
long long	time_diff(long long t1, long long t2);

//_______________________________
/*			ERROR UTILS			*/
int			print_error_and_return(int errnum);

#endif