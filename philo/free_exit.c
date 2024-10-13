/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:08:14 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/13 17:05:22 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "philo.h"

static void ft_free_philo(t_philo *p)
{
	if (p->philo)
		p->philo = 0;
	if (p->fork_l)
		pthread_mutex_destroy(p->fork_l);
	if (p->fork_r)
		pthread_mutex_destroy(p->fork_r);
	if (p->write_lock)
		pthread_mutex_destroy(p->write_lock);
	if (p->meal_lock)
		pthread_mutex_destroy(p->meal_lock);
	if (p)
		free(p);
}

void	ft_free_philos(t_philo **ps, int nbr_of_philos)
{
	int	i;

	i = -1;
	if (ps)
	{
		if (ps[0]->w)
		{
			if (ps[0]->w->waiter_lock)
			{
				pthread_mutex_destroy(ps[0]->w->waiter_lock);
				free(ps[0]->w->waiter_lock);
			}
			free(ps[0]->w);
		}
		while (++i < nbr_of_philos - 1)
			ft_free_philo(ps[i]);
		if (ps[i])
		{
			free(ps[i]);
			ps[i] = NULL;
		}
		free(ps);
		ps = NULL;
	}
}

void	ft_free_forks(t_mtx *fs, int nbr_of_philos)
{
	int	i;

	i = 0;
	if (fs)
	{
		while (i < nbr_of_philos - 1)
		{
			pthread_mutex_destroy(&fs[i]);
			i++;
		}
		free(fs);
	}
}

void	ft_free_data(t_data *d)
{
	if (d)
	{
		pthread_mutex_destroy(&d->meal_lock);
		pthread_mutex_destroy(&d->write_lock);
		if (d->ps)
			ft_free_philos(d->ps, d->nbr_of_philos);
		free(d);
	}
}

int	ft_err_exit(t_data *d, t_mtx *fs, const char *err_message, int ret)
{
	printf("Error!\n%s\n", err_message);
	if (d)
		ft_free_data(d);
	if (fs)
		ft_free_forks(fs, d->nbr_of_philos);
	return (ret);
}

