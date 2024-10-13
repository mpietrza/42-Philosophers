/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:48:34 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/13 16:48:40 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_waiter(t_waiter *w)
{
	w->waiter_lock = (t_mtx *)malloc(sizeof(t_mtx));
	if (!w->waiter_lock)
		return (FALSE);
	w->state = PREPARING;
	if (pthread_mutex_init(w->waiter_lock, NULL) != 0)
		return (FALSE);
	return (TRUE);
}

static void	ft_assign_forks(t_philo *p, t_mtx *fs)
{
	p->fork_l = &fs[p->philo_id - 1];
	if (p->philo_id == p->nbr_of_philos)
		p->fork_r = &fs[0];
	else
		p->fork_r = &fs[p->philo_id];

}

int ft_init_philos(t_data *d, t_mtx *fs, t_waiter *w, t_philo **ps)
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
		ft_parse_philo(d, ps[i]);
		ps[i]->philo_id = i + 1;
		ps[i]->is_eating = FALSE;
		ps[i]->nbr_of_meals_eaten = 0;
		ps[i]->d = d;
		ps[i]->w = w;
		ps[i]->when_sim_started = &d->when_sim_started;
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

void	ft_assign_time_and_start(t_philo **ps)
{
	int	i;

	i = 0;
	*ps[0]->when_sim_started = ft_crnt_tm();
	while (i < ps[0]->nbr_of_philos)
	{
		pthread_mutex_lock(ps[i]->meal_lock);
		ps[i]->when_was_last_meal = *ps[0]->when_sim_started;
		pthread_mutex_unlock(ps[i]->meal_lock);
		i++;
	}
	pthread_mutex_lock(ps[0]->w->waiter_lock);
	ps[0]->w->state = SERVING;
	pthread_mutex_unlock(ps[0]->w->waiter_lock);
}
