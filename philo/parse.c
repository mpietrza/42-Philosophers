/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:03:09 by mpietrza          #+#    #+#             */
/*   Updated: 2024/06/05 17:10:52 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	ft_free_data(t_data *d)
{
	if (d)
	{
		if (d->death_lock)
			pthread_mutex_destroy(d->death_lock);
		if (d->meal_lock)
			pthread_mutex_destroy(d->meal_lock);
		if (d->write_lock)
			pthread_mutex_destroy(d->write_lock);
		if (d->philos)
			ft_free_philos(philos);
		free(d);
	}
}

void	ft_init_forks(t_mtx *fs, size_t nbr_of_philos)
{
	size_t	i;

	i = 0;
	while (i < nbr_of_philos)
	{
		pthread_mutex_init(&fs[i], NULL);
		i++;
	}
}

void	ft_init_philos(t_philo *ps, t_data *d, t_mtx *fs,
		char **argv)
{
	size_t	i;

	i = 0;
	while (i < d->nbr_of_philos)
	{
		ps[i].id = i + 1;
		ps[i].is_eating = false;
		ps[i].nbr_of_meals_eaten = 0;
		ps[i].when_was_last_meal = ft_crnt_tm();
		ps[i].is_dead = &d->is_dead_flag;
		ps[i].fork_l = &fs[i];
		if (i = 0)
			ps[i].fork_r = &fs[d.nbr_of_philos - 1];
		else
			ps[i].fork_r = &fs[i - 1];
		ps[i].write_lock = &d->write_lock;
		ps[i].death_lock = &d->death_lock;
		ps[i].meal_lock = &d->meal_lock;
		i++;
	}
}


t_data	*ft_parse_input(int argc, char **argv, t_philo *ps)
{
	t_data	*d;
	
	d = (t_data *)malloc(sizeof(t_data));
	if (!d)
		return (NULL);
	d->nbr_of_philos = ft_atoi_secured(argv[1]);
	d->tm_t_die = ft_atoi_secured(argv[2]) * 1000;
	d->tm_t_eat = ft_atoi_secured(argv[3]) * 1000;
	d->tm_t_sleep = ft_atoi_secured(argv[4]) * 1000;
	if (argc == 6)
		d->nbr_of_meals_per_philo = ft_atoi_secured(argv[5]);
	else
		d->nbr_of_meals_per_philo = -2;
	d->when_simulation_started = 0;
	d->is_dead_flag = false;
	pthread_mutex_init(&d->write_lock, NULL);
	pthread_mutex_init(&d->death_lock, NULL);
	pthread_mutex_init(&d->meal_lock, NULL);
	d->atoi_errno = 0;
	d->ps = ps;
}
