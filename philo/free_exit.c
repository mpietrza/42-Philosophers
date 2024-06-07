/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:08:14 by mpietrza          #+#    #+#             */
/*   Updated: 2024/06/07 16:19:33 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "philo.h"

void	ft_free_philos(t_philo *ps, size_t nbr_of_philos)
{
	size_t	i;

	i = 0;
	if (ps)
	{
		while (i < nbr_of_philos)
		{
			if (ps[i].fork_l)
				pthread_mutex_destroy(ps[i].fork_l);
			if (ps[i].fork_r)
				pthread_mutex_destroy(ps[i].fork_r);
		}
		free (ps);
	}
}

void	ft_free_data(t_data *d)
{
	if (d)
	{
		if (&d->death_lock)
			pthread_mutex_destroy(&d->death_lock);
		if (&d->meal_lock)
			pthread_mutex_destroy(&d->meal_lock);
		if (&d->write_lock)
			pthread_mutex_destroy(&d->write_lock);
		if (d->ps)
			ft_free_philos(d->ps, d->nbr_of_philos);
		free(d);
	}
}

void	ft_free_all(t_philo *ps, t_data *d)
{
	size_t	i;

	i = 0;
	if (ps)
	{
		if(d)
			ft_free_philos(ps, d->nbr_of_philos);
		else
		{
			while (philos[i])
				i++;
			ft_free_philos(ps, i);
		}
	}
	if (d)
		ft_free_data(d);
}
