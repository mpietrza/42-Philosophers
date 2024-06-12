/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:48:31 by mpietrza          #+#    #+#             */
/*   Updated: 2024/06/12 19:03:01 by mpietrza         ###   ########.fr       */
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
	size_t		when_sim_started;
	bool		is_dead_flag;
	t_mtx		write_lock;
	t_mtx		death_lock;
	t_mtx		meal_lock;
	int		atoi_errno;
	t_philo		*ps;
}			t_data;


/***************************** list of functions ******************************/
/*actions.c*/
void	ft_message(char *s, t_philo *p, t_data *d, int id);
void	ft_eat(t_philo *p, t_data *d);
void	ft_sleep(t_philo *p, t_data *d);
void	ft_think(t_philo *p, t_data *d);

/*atoi_secured.c*/
size_t	ft_atoi_pos_secured(const char *str);

/*arg_check.c*/
bool     ft_my_isdigit(int c);
bool    ft_check_argv(const char **argv);
//char  *ft_strchr(const char *s, int c);


/*free_exit.c*/
void	ft_free_philos(t_philo *ps, size_t nbr_of_philos);
void	ft_free_data(t_data *d);
void    ft_free_all(t_philo *ps, t_data *d);

/*init_parse.c*/
void	ft_init_forks(t_mtx *fs, size_t nbr_of_philos);
void	ft_init_philos(t_philo *ps, t_data *d, t_mtx *fs, char **argv);
t_data	*ft_parse_input(int argc, char **argv, t_philo *ps);

/*monitoring.c*/
bool	ft_is_philo_dead(t_philo *p, size_t time_to_die);
bool	ft_has_anyone_died(t_philo *ps);
bool    ft_have_all_eaten(t_philo *ps);
void    *ft_monitoring(void *ptr);

/*!!!!!!philo.c!!!!!!*/

/*threads.c*/
bool    ft_death_loop(t_philo *p, t_data *d);
void	*ft_philo_routine(void *ptr);
int	ft_thread_create(t_data *d, t_mtx *fs);

/*utils_time.c*/
size_t	ft_crnt_tm(void);
bool	ft_usleep(size_t millisecs);

#endif
