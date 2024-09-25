/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:18:01 by mpietrza          #+#    #+#             */
/*   Updated: 2024/09/25 16:59:44 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_death_loop(t_philo *p, t_data *d)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(&d->death_lock);
	if (*p->is_dead == true)
		ret = true;
	pthread_mutex_unlock(&d->death_lock);
	return (ret);
}

void	*ft_philo_routine(void *ptr)
{
	t_philo	*p;
	t_data	*d;

	p = (t_philo *)ptr;
	d = p->d;
	if (p->philo_id % 2 == 0)
		ft_usleep(1);//!?
	while (!ft_death_loop(p, d))
	{
		ft_eat(p, d);
		ft_sleep(p, d);
		ft_think(p, d);
	}
	return (ptr);
}

bool	ft_thread_create(t_data *d)
{
	pthread_t	controller;
	size_t		i;

	if (pthread_create(&controller, NULL, &ft_monitoring, &d->ps) != 0)
	{
		ft_err_exit(d, "Pthread_create error");
		return (false);
	}
	i = 0;
	while (i < d->nbr_of_philos)
	{
		if (pthread_create(&d->ps[i].thread_id, NULL, &ft_philo_routine,
					&d->ps[i]) != 0)
		{
			ft_err_exit(d, "Pthread_create error");
			return (false);
		}
		i++;
	}
	i = 0;
	if (pthread_join(controller, NULL) != 0)
	{
		ft_err_exit(d, "Pthread_join error");
		return (false);
	}
	while (i < d->nbr_of_philos)
	{
		if (pthread_join(d->ps[i].thread_id, NULL) != 0)
		{
			ft_err_exit(d, "Pthread_join error");
			return (false);
		}
		i++;
	}
	return (true);
}
