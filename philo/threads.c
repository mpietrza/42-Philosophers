/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:18:01 by mpietrza          #+#    #+#             */
/*   Updated: 2024/06/12 18:58:33 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_death_loop(t_philo *p, t_data *d)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(d->death_lock);
	if (*philo->is_dead == true)
		ret = true;
	pthread_mutex_unlock(d->death_lock);
	return (ret);
}

void	*ft_philo_routine(void *ptr)
{
	t_philo	*p;

	p = (t_philo *)ptr;
	if (p->philo_id % 2 == 0)
		ft_usleep(1);//!?
	while (!death_loop(p))
	{
		ft_eat(p);
		ft_sleep(p);
		ft_think(p);
	}
	return (ptr);
}

int	ft_thread_create(t_data *d, t_philo *ps)
{
	pthread_t	controller;
	size_t		i;

	if (pthread_create(&controller, NULL, &monitoring, d->nbr_of_philos) != 0)
	{
		printf("Error!\nPthread_create error\n");
		ft_free_all(ps, d);
	}
	i = 0;
	while (i < d->nbr_of_philos)
	{
		if (pthread_create(&d->ps[i].thread_id, NULL) != 0)
		{
			printf("Error!\nPthread_create error\n");
			ft_free_all(ps, d);
		}
		i++;
	}
	i = 0;
	if (pthread_join(controller, NULL) != 0)
	{
		printf("Error!\nPthread_join error\n");
		ft_free_all(ps, d);
	}
	while (i < d->nbr_of_philos)
	{
		if (pthread_join(d->ps[i].thread_id, NULL) != 0)
		{
			printf("Error!\nPthread_join error\n");
			ft_free_all(ps, d);
		}
		i++;
	}
	return (0);//why not void?
}
