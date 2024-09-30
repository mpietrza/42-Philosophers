/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:10:57 by mpietrza          #+#    #+#             */
/*   Updated: 2024/09/30 15:37:25 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, const char **argv)
{
	t_data	*d;
	t_mtx	*fs;
	size_t	nbr_of_philos;
	size_t	i;

	d = NULL;
	if (!(argc == 5 || argc == 6) || ft_check_argv(argv) == false)
		return (ft_err_exit(NULL, NULL, "Wrong input", 1));
	nbr_of_philos = ft_atoi_pos_secured(argv[1]);
	fs = (t_mtx *)malloc(sizeof(t_mtx) * nbr_of_philos);//forks
	if (!fs)
		return (ft_err_exit(d, NULL, "Memory allocation error", 1));
	printf("Debug: fs address after malloc = %p\n", (void *)fs);
	if (ft_init_forks(fs, nbr_of_philos) == false)
		return (ft_err_exit(d, NULL, "Forks initialization error", 1));
	printf("Debug: Forks initialized\n");
	d = ft_parse_input(argc, argv, fs);//parsing input
	if (!d)
		return (ft_err_exit(NULL, NULL, "Memory allocation error", 1));
	printf("Debug: d address after parsing = %p\n", (void *)d);
	d->ps = ft_init_philos(d, fs);
	i = 0;
	while (i < d->nbr_of_philos)
	{
		printf("Debug: ps[%zu] address = %p\n", i, (void *)d->ps[i]);
		i++;
	} 
	if (!d->ps)
		return (ft_err_exit(d, fs, "Philos initialization error", 1));
	printf("Debug: Philosophers initialized, ps address = %p\n", (void *)d->ps);
	d->when_sim_started = ft_crnt_tm();
	if (ft_thread_create(d) == false)
		return (ft_err_exit(d, fs, "Thread creation error", 1));
	printf("Debug: Threads created\n");
	if (ft_monitoring(d) == false)
		return (ft_err_exit(d, fs, "Thread monitoring error", 1));
	printf("Debug: Monitoring completed\n");
	free(fs);
	ft_free_data(d);
	return (0);
}


static void	ft_assign_forks(t_philo *p, t_mtx *fs)
{
	p->fork_l =  &fs[p->philo_id];
	p->fork_r = &fs[(p->philo_id + 1) % p->d->nbr_of_philos];
	if (p->philo_id % 2)
	{
		p->fork_l = &fs[(p->philo_id + 1) % p->d->nbr_of_philos];
		p->fork_r = &fs[p->philo_id];
	}
}

t_philo	**ft_init_philos(t_data *d, t_mtx *fs)
{
	unsigned int	i;
	t_philo			**ps;

	ps = (t_philo **)malloc(sizeof(t_philo *) * d->nbr_of_philos);
	if (!ps)
		return (NULL);
	i = 0;
	while (i < d->nbr_of_philos)
	{
		ps[i] = malloc(sizeof(t_philo));
		if (!ps[i])
		{
			while (i > 0)
				free(ps[--i]);
			free(ps);
			return (NULL);
		}
		ps[i]->philo_id = i + 1;
		ps[i]->is_eating = false;
		ps[i]->nbr_of_meals_eaten = 0;
		ps[i]->when_was_last_meal = ft_crnt_tm();
		ps[i]->is_dead = &d->is_dead_flag;
		ps[i]->write_lock = &d->write_lock;
		ps[i]->death_lock = &d->death_lock;
		ps[i]->meal_lock = &d->meal_lock;
		ps[i]->d = d;
		ft_assign_forks(ps[i], fs);
		i++;
	}
	return (ps);
}


bool	ft_init_forks(t_mtx *fs, size_t nbr_of_philos)
{
	size_t	i;

	i = 0;
	while (i < nbr_of_philos)
	{
		if (pthread_mutex_init(&fs[i], NULL) != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&fs[--i]);
			return (false);
		}
		i++;
	}
	return (true);
}

t_data	*ft_parse_input(int argc, const char **argv, t_mtx *fs)
{
	t_data	*d;
	
	d = (t_data *)malloc(sizeof(t_data));
	if (!d)
		return (NULL);
	printf("argv[1] = %s\n", argv[1]);
	d->nbr_of_philos = ft_atoi_pos_secured(argv[1]);
	printf("d->nbr_of_philos = %zu\n", d->nbr_of_philos);
	d->tm_t_die = ft_atoi_pos_secured(argv[2]) * 1000;
	d->tm_t_eat = ft_atoi_pos_secured(argv[3]) * 1000;
	d->tm_t_sleep = ft_atoi_pos_secured(argv[4]) * 1000;
	if (argc == 6)
		d->nbr_of_meals_per_philo = ft_atoi_pos_secured(argv[5]);
	else
		d->nbr_of_meals_per_philo = (size_t)-2;
	d->when_sim_started = ft_crnt_tm() + (d->nbr_of_philos * 2 * 10);
	d->is_dead_flag = false;
	pthread_mutex_init(&d->write_lock, NULL);
	pthread_mutex_init(&d->death_lock, NULL);
	pthread_mutex_init(&d->meal_lock, NULL);
	d->atoi_errno = 0;
	d->ps = ft_init_philos(d, fs);
	return (d);
}

