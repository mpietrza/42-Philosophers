/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:48:31 by mpietrza          #+#    #+#             */
/*   Updated: 2024/06/05 17:10:55 by mpietrza         ###   ########.fr       */
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
//			pthread_mutex_init, pthread_mutex_destroy,
//			pthread_mutex_lock, pthread_mutex_unlock

/*struct - for data transfer thoughout the program*/

typedef pthread_mutex_t t_mtx;

typedef struct s_philo
{
	pthread_t	thread_id; // a philo is a thread
	size_t		philo_id;
	bool		is_eating;
	size_t		nbr_of_meals_eaten;
	size_t		when_was_last_meal; 
	bool		*is_dead;
	t_mtx		*fork_l;
	t_mtx		*fork_r;
	t_mtx		*write_lock;
	t_mtx		*death_lock;
	t_mtx		*meal_lock;
}			t_philo;

typedef struct s_data
{
	
	size_t		nbr_of_philos;
	size_t		tm_t_die;
	size_t		tm_t_eat;	
	size_t		tm_t_sleep;	
	size_t		nbr_of_meals_per_philo; // if -1 = error; if -2 = no arg
	long		when_sim_started;
	bool		is_dead_flag;
	t_mtx		write_lock;
	t_mtx		death_lock;
	t_mtx		meal_lock;
	int		atoi_errno;
	t_philo		*ps;
}			t_data;


/***************************** list of functions ******************************/
/*actions.c*/
//void	w_status(char *s, t_data *d, t_mutex *m, int i);
//void	ft_take_fork(t_data *d, t_mutex *m, int i);
//void	ft_eat(t_data *d, t_mutex *m, int i);
//void	ft_sleep(t_data *d, t_mutex *m, int i);

/*atoi_secured.c*/
size_t	ft_atoi_pos_secured(const char *str);

/*init_mutex_and_thread.c*/
int ft_init_mutex(t_data *d);

/*parse.c*/
t_data	*ft_parse_input(int argc, char **argv);

/*!!!!!!philo.c!!!!!!*/

/*routine.c*/
int		is_philo_dead(t_philo *t);
void	*philo_routine(void *f);

/*utils_time*/
long	ft_crnt_tm(void);
void	ft_usleep(int cndtn);


#endif
