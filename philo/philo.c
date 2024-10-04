/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:10:57 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/04 15:44:43 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, const char **argv)
{
	t_data	*d;
	t_philo	**ps;
	t_mtx	*fs;
	int	nbr_of_philos;

	if (!(argc == 5 || argc == 6) || ft_check_argv(argv) == FALSE)
		return (ft_err_exit(NULL, NULL, "Wrong input", 1));
	nbr_of_philos = (int)ft_atos_t_positive(argv[1]);
	fs = (t_mtx *)malloc(sizeof(t_mtx) * nbr_of_philos);
	if (!fs)
		return (ft_err_exit(NULL, NULL, "Memory allocation error", 1));
	if (ft_init_forks(fs, nbr_of_philos) == FALSE)
		return (ft_err_exit(NULL, fs, "Forks initialization error", 1));
	d = (t_data *)malloc(sizeof(t_data));
	if (!d)
		return (ft_err_exit(NULL, fs, "Memory allocation error", 1));
	ft_parse_input(argc, argv, d);
	ps = (t_philo **)malloc(sizeof(t_philo *) * d->nbr_of_philos);
	if (!ps)
		return (ft_err_exit(NULL, NULL, "Memory allocation error", 1));
	d->ps = ps;
	ft_init_philos(d, fs, ps);
	if (ft_thread_create(ps) == FALSE)
		return (ft_err_exit(d, fs, "Thread creation error", 1));
	if (ft_monitoring((void *)ps) == NULL)
		return (ft_err_exit(d, fs, "Thread monitoring error", 1));
	free(fs);
	ft_free_data(d);
	return (0);
}

static void	ft_assign_forks(t_philo *p, t_mtx *fs)
{
	p->fork_l = &fs[p->philo_id - 1];
	if (p->philo_id == p->nbr_of_philos)
		p->fork_r = &fs[0];
	else
		p->fork_r = &fs[p->philo_id];

}

int ft_init_philos(t_data *d, t_mtx *fs, t_philo **ps)
{
	int			i;

	i = 0;
	while (i < d->nbr_of_philos)
	{
		ps[i] = malloc(sizeof(t_philo));
		if (!ps[i])
		{
			while (i > 0)
				free(ps[--i]);
			free(ps);
			return (FALSE);
		}
		ps[i]->nbr_of_philos = d->nbr_of_philos;
		ps[i]->tm_t_die = (time_t)ft_atos_t_positive(d->argv[2]);
		ps[i]->tm_t_eat = (time_t)ft_atos_t_positive(d->argv[3]);
		ps[i]->tm_t_sleep = (unsigned long long)ft_atos_t_positive(d->argv[4]);
		if (d->argc == 6)
			ps[i]->nbr_of_meals_per_philo = (int)ft_atos_t_positive(d->argv[5]);
		else
			ps[i]->nbr_of_meals_per_philo = -1;
		ps[i]->philo_id = i + 1;
		ps[i]->is_eating = FALSE;
		ps[i]->nbr_of_meals_eaten = 0;
		ps[i]->is_anyone_dead = &d->is_anyone_dead_flag;
		ps[i]->are_all_full = &d->are_all_full_flag;
		ps[i]->write_lock = &d->write_lock;
		ps[i]->death_lock = &d->death_lock;
		ps[i]->full_lock = &d->full_lock;
		ps[i]->meal_lock = &d->meal_lock;
		ps[i]->d = d;
		ps[i]->when_sim_started = ft_crnt_tm();
		ft_assign_forks(ps[i], fs);
		i++;
	}
	return (TRUE);
}


int	ft_init_forks(t_mtx *fs, int nbr_of_philos)
{
	int	i;

	i = 0;
	while (i <  nbr_of_philos)
	{
		if (pthread_mutex_init(&fs[i], NULL) != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&fs[--i]);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

void	ft_parse_input(int argc, const char **argv, t_data *d)
{
	d->argv = argv;
	d->argc = argc;
	d->nbr_of_philos = (int)ft_atos_t_positive(argv[1]);
	d->is_anyone_dead_flag = FALSE;
	pthread_mutex_init(&d->write_lock, NULL);
	pthread_mutex_init(&d->death_lock, NULL);
	pthread_mutex_init(&d->full_lock, NULL);
	pthread_mutex_init(&d->meal_lock, NULL);
	d->atoi_errno = 0;
}

