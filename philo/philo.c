/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:10:57 by mpietrza          #+#    #+#             */
/*   Updated: 2024/09/25 17:25:45 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, const char **argv)
{
	t_data	*d;
	t_mtx	*fs;

	if (!(argc == 5 || argc == 6) || ft_check_argv(argv) == false)
	{
		printf("Error!\nWrong input\n");
		return (1);
	}
	d = ft_parse_input(argc, argv);//parsing input
	if (!d)
	{
		printf("Error!\nMemory allocation error\n");
		return (1);
	}
	printf("Debug: d address after parsing = %p\n", (void *)d);
	fs = (t_mtx *)malloc(sizeof(t_mtx) * d->nbr_of_philos);//forks
	if (!fs)
	{
		ft_err_exit(d, "Memory allocation error");
		return (1);
	}
	printf("Debug: fs address after malloc = %p\n", (void *)fs);
	if (ft_init_forks(fs, d) == false)
	{
		free(fs);
		ft_free_data(d);
		return (1);
	}
		printf("Debug: Forks initialized\n");
	d->ps = (ft_init_philos(d, fs));
	if (!d->ps)
	{
		free(fs);
		ft_free_data(d);
		return (1);
	}
	printf("Debug: Philosophers initialized, ps address = %p\n", (void *)d->ps);
	d->when_sim_started = ft_crnt_tm();
	if (ft_thread_create(d) == false)
	{
		free(fs);
		ft_free_data(d);
		return (1);
	}
	printf("Debug: Threads created\n");
	if (ft_monitoring(d->ps) == false)
	{
		printf("Error in monitoring\n");
		free(fs);
		ft_free_data(d);
		return (1);
	}
	printf("Debug: Monitoring completed\n");
	free(fs);
	ft_free_data(d);
	return (0);
}

t_philo	*ft_init_philos(t_data *d, t_mtx *fs)
{
	size_t	i;
	t_philo	*ps;

	i = 0;
	ps = (t_philo *)malloc(sizeof(t_philo) * d->nbr_of_philos);
	if (!ps)
	{
		ft_err_exit(d, "Memory allocation error - philos");
		return (NULL);
	}
	while (i < d->nbr_of_philos)
	{
		ps[i].philo_id = i + 1;
		ps[i].is_eating = false;
		ps[i].nbr_of_meals_eaten = 0;
		ps[i].when_was_last_meal = ft_crnt_tm();
		ps[i].is_dead = &d->is_dead_flag;
		ps[i].fork_l = &fs[i];
		if (i == 0)
			ps[i].fork_r = &fs[d->nbr_of_philos - 1];
		else
			ps[i].fork_r = &fs[i - 1];
		ps[i].write_lock = &d->write_lock;
		ps[i].death_lock = &d->death_lock;
		ps[i].meal_lock = &d->meal_lock;
		ps[i].d = d;
		i++;
	}
	return (ps);
}

bool	ft_init_forks(t_mtx *fs, t_data *d)
{
	size_t	i;

	i = 0;
	while (i < d->nbr_of_philos)
	{
		if (pthread_mutex_init(&fs[i], NULL) != 0)
		{
			ft_err_exit(d, "Error initializing fork mutex");
			return (false);
		}
		i++;
	}
	return (true);
}

t_data	*ft_parse_input(int argc, const char **argv)
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
	d->when_sim_started = 0;
	d->is_dead_flag = false;
	pthread_mutex_init(&d->write_lock, NULL);
	pthread_mutex_init(&d->death_lock, NULL);
	pthread_mutex_init(&d->meal_lock, NULL);
	d->atoi_errno = 0;
	d->ps = NULL;
	return (d);
}

