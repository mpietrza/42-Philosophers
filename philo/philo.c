/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:10:57 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/01 19:35:26 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, const char **argv)
{
	t_data	*d;
	t_mtx	*fs;
	size_t	nbr_of_philos;

	if (!(argc == 5 || argc == 6) || ft_check_argv(argv) == FALSE)
		return (ft_err_exit(NULL, NULL, "Wrong input", 1));
	nbr_of_philos = (int)ft_atoi_pos_secured(argv[1]);
	fs = (t_mtx *)malloc(sizeof(t_mtx) * nbr_of_philos);//forks
	if (!fs)
		return (ft_err_exit(NULL, NULL, "Memory allocation error", 1));
	printf("Debug: fs address after malloc = %p\n", (void *)fs);
	if (ft_init_forks(fs, nbr_of_philos) == FALSE)
		return (ft_err_exit(NULL, fs, "Forks initialization error", 1));
	printf("Debug: Forks initialized\n");
	d = (t_data *)malloc(sizeof(t_data));
	if (!d)
		return (ft_err_exit(NULL, fs, "Memory allocation error", 1));
	ft_parse_input(argc, argv, d, fs);//parsing input
	if (!d)
		return (ft_err_exit(NULL, NULL, "Memory allocation error", 1));
	printf("Debug: d address after parsing = %p\n", (void *)d);
	ft_print_data(d);
	printf("Debug: Philosophers initialized, ps address = %p\n", (void *)d->ps);
	ft_print_data(d);
	d->when_sim_started = ft_crnt_tm();
	if (ft_thread_create(d) == FALSE)
		return (ft_err_exit(d, fs, "Thread creation error", 1));
	printf("Debug: Threads created\n");
	ft_print_data(d);
	if (ft_monitoring((void *)d) == NULL)
		return (ft_err_exit(d, fs, "Thread monitoring error", 1));
	printf("Debug: Monitoring completed\n");
	ft_print_data(d);
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

t_philo	**ft_init_philos(t_data *d, t_mtx *fs, int nbr_of_philos)
{
	int			i;
	t_philo		**ps;

	ps = (t_philo **)malloc(sizeof(t_philo *) * nbr_of_philos);
	if (!ps)
		return (NULL);
	i = 0;
	while (i < nbr_of_philos)
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
		ps[i]->is_eating = FALSE;
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


int	ft_init_forks(t_mtx *fs, int nbr_of_philos)
{
	int	i;

	i = 0;
	while (i <  nbr_of_philos - 1)
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

void	ft_parse_input(int argc, const char **argv, t_data *d, t_mtx *fs)
{
	printf("argv[1] = %s\n", argv[1]);
	d->nbr_of_philos = (int)ft_atoi_pos_secured(argv[1]);
	printf("!!!!d->nbr_of_philos = %d\n", d->nbr_of_philos);
	d->tm_t_die = (unsigned long long)ft_atoi_pos_secured(argv[2]);
	d->tm_t_eat = (unsigned long long)ft_atoi_pos_secured(argv[3]);
	d->tm_t_sleep = (unsigned long long)ft_atoi_pos_secured(argv[4]);
	if (argc == 6)
		d->nbr_of_meals_per_philo = (int)ft_atoi_pos_secured(argv[5]);
	else
		d->nbr_of_meals_per_philo = -2;
	d->when_sim_started = ft_crnt_tm() + (d->nbr_of_philos * 2 * 10);
	d->is_dead_flag = FALSE;
	pthread_mutex_init(&d->write_lock, NULL);
	pthread_mutex_init(&d->death_lock, NULL);
	pthread_mutex_init(&d->meal_lock, NULL);
	d->atoi_errno = 0;
	d->ps = ft_init_philos(d, fs, d->nbr_of_philos);

}

