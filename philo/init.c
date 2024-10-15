/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milosz <milosz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:16:05 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/15 17:50:51 by milosz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data *ft_init_data(int argc, const char **argv) 
{
	t_data		*d;

	d = (t_data *)malloc(sizeof(t_data));
	if (!d)
		return (NULL);
	if (ft_parse_input(argc, argv, d) == FALSE)
	{
		free(d);
		return (NULL);
	}
	return (d);
}

t_wtr	*ft_init_wtr(void)
{
	t_wtr	*w;

	w = (t_wtr *)malloc(sizeof(t_wtr));
	if (!w)
		return (NULL);
	w->waiter_lock = (t_mtx *)malloc(sizeof(t_mtx));
	if (!w->waiter_lock)
	{
		free(w);
		return (NULL);
	}
	w->state = PREPARING;
	if (pthread_mutex_init(w->waiter_lock, NULL) != 0)
	{
		free(w->waiter_lock);
		free(w);
		return (NULL);
	}
	return (w);
}


static void	ft_assign_forks(t_philo *p, t_mtx *fs)
{
	p->fork_l = &fs[p->philo_id - 1];
	if (p->philo_id == p->nbr_of_philos)
		p->fork_r = &fs[0];
	else
		p->fork_r = &fs[p->philo_id];

}


t_philo	**ft_init_philos(t_data *d, t_mtx *fs, t_wtr *w)
{
	t_philo		**ps;
	int			i;

	i = 0;
	ps = (t_philo **)malloc(sizeof(t_philo *) * d->nbr_of_philos);
	if (!ps)
		return (NULL);
	while (i < d->nbr_of_philos)
	{
		ps[i] = malloc(sizeof(t_philo));
		if (!ps[i])
		{
			ft_free_philos(ps, i);
			return (NULL);
		}
		ft_parse_philo(d, ps[i]);
		ps[i]->philo_id = i + 1;
		ps[i]->d = d;
		ps[i]->w = w;
		ps[i]->when_sim_started = &d->when_sim_started;
		ft_assign_forks(ps[i], fs);
		i++;
	}
	d->ps = ps;
	return (ps);
}

t_mtx	*ft_init_forks(int nbr_of_philos)
{
	int		i;
	t_mtx	*fs;

	fs = (t_mtx *)malloc(sizeof(t_mtx) * nbr_of_philos);
	if (!fs)
		return (NULL);
	i = 0;
	while (i < nbr_of_philos)
	{
		if (pthread_mutex_init(&fs[i], NULL) != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&fs[--i]);
			return (NULL);
		}
		i++;
	}
	return (fs);
}
