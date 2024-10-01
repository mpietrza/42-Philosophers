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
	pthread_t	thread_id; // a philo is a thread
	int		philo_id;
	int		is_eating;
	int		nbr_of_meals_eaten;
	time_t		when_was_last_meal; 
	int		*is_dead;
	t_mtx		*fork_l;
	t_mtx		*fork_r;
	t_mtx		*write_lock;
	t_mtx		*death_lock;
	t_mtx		*meal_lock;
	t_data		*d;
}			t_philo;

typedef struct s_data
{
	
	int					nbr_of_philos;
	unsigned long long	tm_t_die;
	unsigned long long	tm_t_eat;	
	unsigned long long	tm_t_sleep;	
	int 				nbr_of_meals_per_philo; // if -1 = error; if -2 = no arg
	unsigned long long	when_sim_started;
	int					is_dead_flag;
	t_mtx				write_lock;
	t_mtx				death_lock;
	t_mtx				meal_lock;
	int					atoi_errno;
	t_philo				**ps;
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
int	ft_my_isdigit(int c);
int	ft_check_argv(const char **argv);
//char  *ft_strchr(const char *s, int c);


/*free_exit.c*/
void	ft_free_philos(t_philo *ps, int nbr_of_philos);
void	ft_free_data(t_data *d);
int	ft_err_exit(t_data *d, t_mtx *fs, const char *err_message, int ret);
//void	ft_free_all(t_philo *ps, t_data *d);

/*init_parse.c*/
int	ft_init_forks(t_mtx *fs, int nbr_of_philos);
t_philo	**ft_init_philos(t_data *d, t_mtx *fs, int nbr_of_philos);
void	ft_parse_input(int argc, const char **argv, t_data *d, t_mtx *fs);

/*monitoring.c*/
int	ft_is_philo_dead(t_philo *p, size_t time_to_die);
int	ft_has_anyone_died(t_data *d);
int	ft_have_all_eaten(t_data *d, t_philo *ps);
void	*ft_monitoring(void *ptr);

/*!!!!!!philo.c!!!!!!*/

/*threads.c*/
int    ft_death_loop(t_philo *p, t_data *d);
void	*ft_philo_routine(void *ptr);
int	ft_thread_create(t_data *d);

/*utils_time.c*/
unsigned long long	ft_crnt_tm(void);
int	ft_usleep(size_t millisecs);

/*utils.c*/
void	ft_print_data(t_data *d);

#endif
