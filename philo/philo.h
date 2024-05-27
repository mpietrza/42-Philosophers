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
typedef struct s_philo
{
	int			num_o_meals;
	long		last_meal;
	int			fork_l;
	int			fork_r;
	struct 		s_data		*d; //!!!??
}				t_philo;

typedef struct s_data
{
	int					philo_init;
	bool				is_smltn_on;
	int					id;
	int					nbr_of_philos;
	int					tm_t_die;
	int					tm_t_eat;
	int					tm_t_sleep;
	int					nbr_o_tms_each_phlsphr_mst_eat;
//	t_philo				*philo;
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
int		ft_atoi_secured(const char *str, t_data *d);

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
