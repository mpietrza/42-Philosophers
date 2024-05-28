/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:48:31 by mpietrza          #+#    #+#             */
/*   Updated: 2024/05/13 17:22:32 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h> //write, usleep
# include <limits.h> //INT_MAX in ft_atoi_secured
# include <stdbool.h> //bools
# include <stdlib.h> //malloc, free
# include <string.h> //memset
# include <stdio.h> //printf
# include <sys/time.h> //gettimeofday
# include <pthread.h> //pthread_create, pthread_detach, pthread_join,
//						pthread_mutex_init, pthread_mutex_destroy,
//						pthread_mutex_lock, pthread_mutex_unlock

/*struct - for data transfer thoughout the program*/

typedef pthread_mutex_t t_mtx;

typedef struct s_fork
{
	t_mtx		fork;
	int			fork_id;
}				t_fork;

typedef struct s_philo
{
	int			id;
	long		num_o_meals;
	bool		is_full;
	long		when_was_last_meal; 
	t_fork		*fork_l;
	t_fork		*fork_r;
	pthread_t	thread_id; // a philo is a thread
}				t_philo;

typedef struct s_table
{
	long			nbr_of_philos;
	long		tm_t_die;
	long		tm_t_eat;
	long		tm_t_sleep;
	long		nbr_of_meals_per_philo; // if -1 = error; if -2 = no arg
	long		when_simulation_started;
	bool		is_smltn_going;
	t_fork		*forks; //array of forks
	t_philo		*philos; // array of philos
}				t_table;

typedef struct s_data
{
	t_table				*t;
	long				s_time;
	int					atoi_error_index;
}						t_data;

typedef struct s_mutex
{
	pthread_t		*thread;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	mutex_last_meal;
	pthread_mutex_t	mutex_stat;
	pthread_mutex_t	mutex_i;
	pthread_mutex_t	mutex_msg;
	pthread_mutex_t	mutex_fork;
}					t_mutex;


/***************************** list of functions ******************************/
/*actions.c*/
void	w_status(char *s, t_data *d, t_mutex *m, int i);
void	ft_take_fork(t_data *d, t_mutex *m, int i);
void	ft_eat(t_data *d, t_mutex *m, int i);
void	ft_sleep(t_data *d, t_mutex *m, int i);

/*atoi_secured.c*/
int		ft_atoi_pos_secured(const char *str);

/*init_mutex_and_thread.c*/
int ft_init_mutex(t_data *d);

/*parse.c*/
void	parse_input(t_data *d, char **argv);

/*!!!!!!philo.c!!!!!!*/
long	get_time(void);
void	string_to_args(t_data *data, int argc, char **argv);
t_data	*data_calloc(int argc, char **argv);

/*routine.c*/
int		is_philo_dead(t_data *d);
void	*philo_routine(void *f);

/*utils_time*/
long	crnt_tm(void);
void	ft_usleep(int cndtn);


#endif
