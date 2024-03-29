/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 10:34:41 by mcorso            #+#    #+#             */
/*   Updated: 2022/10/21 09:20:08 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define PARSING_ERROR_MSG "Parsing error: "
# define ENAN_MSG "Argument is negative, null or not a number."
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

# define FIRST_FORK 0
# define SECOND_FORK 1
# define NB_FORK_PER_PHILO 2

# define ONE_MS 1000

# define TERMINATE 1

# define DED 1
# define NOT_DED 0

# define EATS_MSG "is eating."
# define SLEEPS_MSG "is sleeping."
# define THINKS_MSG "is thinking."
# define TAKES_FORK_MSG "has taken a fork."
//	END ACTION MSGS
# define DIES_MSG "is ded."
# define RATION_MSG "philos have eaten enough."

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
	int				nb_of_meal;
	long long		last_meal;
	pthread_t		thread_id;
	pthread_mutex_t	data_access;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	struct s_global	*globvar;
}				t_philo;

typedef struct s_global {
	struct s_args	args;
	pthread_mutex_t	write;
	pthread_mutex_t	start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	data_access;
	long long		time_ref;
	t_philo			*philos;
	int				is_ded;
	int				terminate;
}				t_global;

//_______________________________
/*			INIT & PARSING		*/
/////////////////////////////////
int			catch_philo_init_and_threading_error(t_global *glo);
int			catch_parsing_and_glo_error(struct s_global *glo, \
										int nb_args, \
										char **args);
//	Mutexes
int			init_single_mutex(pthread_mutex_t *mutex);
int			init_multiple_mutexes(	int nb_of_mutexes, \
									pthread_mutex_t **mutex_array);
int			init_mutex_objects_of_glo(t_global *glo);
void		destroy_mutex_objects_of_glo(t_global *glo);
//	Forks
int			init_fork_objects(pthread_mutex_t **forks, int nb_of_forks);
void		free_forks(pthread_mutex_t **forks);
void		destroy_fork_objects(pthread_mutex_t **forks, int nb_of_forks);

//_______________________________
/*			PHILOS MANAGEMENT	*/
/////////////////////////////////
//	Thread Loop
void		*philo_in_a_thread(void *arg);
//	Eat
void		philo_eats_action(t_philo *philo, t_global *glo, int time_to_eat);
//	Sleep
void		philo_sleeps_action(int philo_id, t_global *glo, int time_to_sleep);
//	Think
void		philo_thinks_action(int philo_id, t_global *glo);
//	Termination
void		termination_manager(t_global *glo);

//_______________________________
/*			LOG MANAGEMENT		*/
/////////////////////////////////
void		print_action_log(int philo_id, t_global *glo, char *action);
//	Time
long long	get_timestamp(void);
long long	time_diff(long long t1, long long t2);

//_______________________________
/*			ERROR UTILS			*/
/////////////////////////////////
int			print_error_and_return(int errnum);

static inline t_philo	init_single_philo(	int index, int number_of_philo, \
											t_global *glo)
{
	t_philo	philosopher;

	philosopher.id = index + 1;
	philosopher.nb_of_meal = 0;
	philosopher.globvar = glo;
	init_single_mutex(&philosopher.data_access);
	philosopher.first_fork = &glo->forks[index + 1];
	philosopher.second_fork = &glo->forks[index];
	if (philosopher.id == number_of_philo)
	{
		philosopher.first_fork = &glo->forks[index];
		philosopher.second_fork = &glo->forks[0];
	}
	return (philosopher);
}

static inline void	end_by_ration_action(t_global *glo)
{
	long long				delta_time_since_start;
	long long				time_ref;

	pthread_mutex_lock(&glo->data_access);
	time_ref = glo->time_ref;
	delta_time_since_start = time_diff(time_ref, get_timestamp());
	pthread_mutex_lock(&glo->write);
	printf("%lli %s\n", delta_time_since_start, RATION_MSG);
	pthread_mutex_unlock(&glo->write);
	glo->terminate = 1;
	pthread_mutex_unlock(&glo->data_access);
}

static inline void	end_by_deth_action(int philo_id, t_global *glo)
{
	long long				delta_time_since_start;
	long long				time_ref;

	pthread_mutex_lock(&glo->data_access);
	time_ref = glo->time_ref;
	delta_time_since_start = time_diff(time_ref, get_timestamp());
	pthread_mutex_lock(&glo->write);
	printf("%lli %i %s\n", delta_time_since_start, philo_id, DIES_MSG);
	pthread_mutex_unlock(&glo->write);
	glo->terminate = 1;
	pthread_mutex_unlock(&glo->data_access);
}

static inline int	get_terminate_var(t_global *glo)
{
	int	ret_val;	

	pthread_mutex_lock(&glo->data_access);
	ret_val = glo->terminate;
	pthread_mutex_unlock(&glo->data_access);
	return (ret_val);
}

#endif