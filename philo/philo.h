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
typedef struct s_phlsphr
{
	int			num_o_meals;
	long		last_meal;
	int			fork_l;
	int			fork_r;
//!?	struct 		s_list		*d;
}				t_phlsphr;

typedef struct s_data
{
	int					phlsphr_init;
	int					stat;
	int					id;
	int					nbr_of_phlsphrs;
	int					tm_t_die;
	int					tm_t_eat;
	int					tm_t_sleep;
	int					nbr_o_tms_each_phlsphr_mst_eat;
	struct t_phlsphr	*phlsphr;
	long				s_time;
	bool				is_atoi_error;
}				t_data;

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
/*atoi_secured.c*/
int		ft_atoi_secured(const char *str, t_data *d);

/*init_mutex_and_thread.c*/
int ft_init_mutex(t_data *d);

/*!!!!!!philo.c!!!!!!*/
long	get_time(void);
void	string_to_args(t_data *data, int argc, char **argv);
t_data	*data_calloc(int argc, char **argv);

#endif
