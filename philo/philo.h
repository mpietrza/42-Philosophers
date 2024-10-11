/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:48:31 by mpietrza          #+#    #+#             */
/*   Updated: 2024/06/13 16:45:04 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define TRUE 1
# define FALSE 0
# define PREPARING 0
# define SERVING 1
# define CLEANING 2
# define LEFT_RIGHT 0
# define RIGHT_LEFT 1
# define TAKEN_FORK 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DIED 4

# include <unistd.h> //write, usleep
# include <limits.h> //INT_MAX in ft_atoi_secured
# include <stdint.h> //ints
# include <stdlib.h> //malloc, free
# include <string.h> //memset
# include <stdio.h> //printf
# include <sys/time.h> //gettimeofday
# include <pthread.h> //pthread_create, pthread_detach, pthread_join,
//			pthread_mutex_init, pthread_mutex_destroy,
//			pthread_mutex_lock, pthread_mutex_unlock

/*struct - for data transfer thoughout the program*/
typedef struct s_data t_data;
typedef struct s_philo t_philo;
typedef struct s_waiter t_waiter;
typedef pthread_mutex_t t_mtx;

typedef struct s_philo
{
	pthread_t	philo; // a philo is a thread
	int			nbr_of_philos;
	int			philo_id;
	int			is_eating;
	int			nbr_of_meals_eaten;
	int 		nbr_of_meals_per_philo; // if -1 = error; if -1 = no arg
	time_t		when_was_last_meal; 
	time_t		tm_t_die;
	time_t		tm_t_eat;	
	time_t		tm_t_sleep;	
	time_t		*when_sim_started;
	t_mtx		*fork_l;
	t_mtx		*fork_r;
	t_mtx		*write_lock;
	t_mtx		*meal_lock;
	t_data		*d;
	t_waiter	*w;
}			t_philo;

typedef struct s_data
{
	const char			**argv;
	//time_t				msg_time;
	int					msg_id;
	int					msg;
	size_t				msg_counter;
	int					argc;
	int					nbr_of_philos;
	t_mtx				write_lock;
	t_mtx				meal_lock;
	int					atoi_errno;
	time_t				when_sim_started;
	t_philo				**ps;
}			t_data;

typedef struct s_waiter
{
	t_mtx		*waiter_lock;
	int			state;
}			t_waiter;

/***************************** list of functions ******************************/
/*actions.c*/
void	ft_message(int msg, t_philo *p, int id);
int		ft_eat(t_philo *p);
int		ft_sleep(t_philo *p);
int		ft_think(t_philo *p);
//int		ft_check_if_philo_is_still_alive(t_philo *p);

/*atoi_secured.c*/
size_t	ft_atos_t_positive(const char *str);

/*arg_check.c*/
int		ft_my_isdigit(int c);
int		ft_check_argv(const char **argv);

/*free_exit.c*/
void	ft_free_philos(t_philo **ps);
void	ft_free_data(t_data *d);
int		ft_err_exit(t_data *d, t_mtx *fs, const char *err_message, int ret);

/*init_parse.c*/
int		ft_init_forks(t_mtx *fs, int nbr_of_philos);
int		ft_init_philos(t_data *d, t_mtx *fs, t_waiter *w, t_philo **ps);
int		ft_parse_input(int argc, const char **argv, t_data *d);
int		ft_init_waiter(t_waiter *w);
void	ft_assign_time_and_start(t_philo **ps);

/*monitoring.c*/
int		ft_is_philo_dead(t_philo *p);
int		ft_has_anyone_died(t_philo **ps);
int		ft_have_all_eaten(t_philo **ps);
void	*ft_monitoring(void *ptr);

/*mtx_getters.c*/
int		ft_get_waiter_state(t_philo *p);
time_t	ft_get_when_was_last_meal(t_philo *p);
int 	ft_get_is_eating(t_philo *p);
int		ft_get_msg(t_philo *p);
void	ft_get_msg_and_print(t_philo *p, size_t *msg_counter_prev);

/*mtx_setters.c*/
void	ft_set_waiter_state(t_philo *p, int state);

/*!!!!!!philo.c!!!!!!*/

/*routine.c*/
void	*ft_philo_routine(void *ptr);

/*threads.c*/
int		ft_thread_create(t_philo **ps);

/*utils_time.c*/
time_t	ft_crnt_tm(void);
int		ft_usleep(time_t millisecs);

/*utils.c*/
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
//size_t	ft_strcpy(char *dst, const char *src);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strdup(const char *s1);

/*utils_itoa.c*/
char	*ft_itoa(int n);

#endif
