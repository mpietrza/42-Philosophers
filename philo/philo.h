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
	time_t		when_sim_started;
	int			*is_anyone_dead;
	int			*are_all_full;
	t_mtx		*fork_l;
	t_mtx		*fork_r;
	t_mtx		*write_lock;
	t_mtx		*death_lock;
	t_mtx		*full_lock;
	t_mtx		*meal_lock;
	t_data		*d;
}			t_philo;

typedef struct s_data
{
	const char			**argv;
	int					argc;
	int					nbr_of_philos;
	int					is_anyone_dead_flag;
	int					are_all_full_flag;
	t_mtx				write_lock;
	t_mtx				death_lock;
	t_mtx				full_lock;
	t_mtx				meal_lock;
	int					atoi_errno;
	t_philo				**ps;
}			t_data;


/***************************** list of functions ******************************/
/*actions.c*/
void	ft_message(char *s, t_philo *p, int id);
void	ft_eat(t_philo *p);
void	ft_sleep(t_philo *p);
void	ft_think(t_philo *p);

/*atoi_secured.c*/
size_t	ft_atos_t_positive(const char *str);

/*arg_check.c*/
int	ft_my_isdigit(int c);
int	ft_check_argv(const char **argv);
//char  *ft_strchr(const char *s, int c);


/*free_exit.c*/
void	ft_free_philos(t_philo **ps);
void	ft_free_data(t_data *d);
int	ft_err_exit(t_data *d, t_mtx *fs, const char *err_message, int ret);
//void	ft_free_all(t_philo *ps, t_data *d);

/*init_parse.c*/
int	ft_init_forks(t_mtx *fs, int nbr_of_philos);
int	ft_init_philos(t_data *d, t_mtx *fs, t_philo **ps);
void	ft_parse_input(int argc, const char **argv, t_data *d);

/*monitoring.c*/
int	ft_is_philo_dead(t_philo *p, size_t time_to_die);
int	ft_has_anyone_died(t_philo **ps);
int	ft_have_all_eaten(t_philo **ps);
void	*ft_monitoring(void *ptr);

/*!!!!!!philo.c!!!!!!*/


/*threads.c*/
int    ft_death_loop(t_philo *p);
void	*ft_philo_routine(void *ptr);
int		ft_thread_create(t_philo **ps);

/*utils_time.c*/
unsigned long long	ft_crnt_tm(void);
int	ft_usleep(size_t millisecs);

/*utils.c*/
void	ft_print_data(t_data *d);

#endif
