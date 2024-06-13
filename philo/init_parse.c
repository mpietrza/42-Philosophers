/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:16:05 by mpietrza          #+#    #+#             */
/*   Updated: 2024/06/13 16:53:30 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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


t_data	*ft_parse_input(int argc, const char **argv)
{
	t_data	*d;
	
	d = (t_data *)malloc(sizeof(t_data));
	if (!d)
		return (NULL);
	d->nbr_of_philos = ft_atoi_pos_secured(argv[1]);
	d->tm_t_die = ft_atoi_pos_secured(argv[2]) * 1000;
	d->tm_t_eat = ft_atoi_pos_secured(argv[3]) * 1000;
	d->tm_t_sleep = ft_atoi_pos_secured(argv[4]) * 1000;
	if (argc == 6)
		d->nbr_of_meals_per_philo = ft_atoi_pos_secured(argv[5]);
	else
		d->nbr_of_meals_per_philo = -2;
	d->when_sim_started = 0;
	d->is_dead_flag = false;
	pthread_mutex_init(&d->write_lock, NULL);
	pthread_mutex_init(&d->death_lock, NULL);
	pthread_mutex_init(&d->meal_lock, NULL);
	d->atoi_errno = 0;
	d->ps = NULL;
	return (d);
}
