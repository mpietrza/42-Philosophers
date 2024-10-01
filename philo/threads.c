/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:18:01 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/01 19:37:44 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_death_loop(t_philo *p, t_data *d)
{
	int	ret;

	ret = FALSE;
	pthread_mutex_lock(&d->death_lock);
	if (*p->is_dead == TRUE)
		ret = TRUE;
	pthread_mutex_unlock(&d->death_lock);
	return (ret);
}

void	*ft_philo_routine(void *ptr)
{
	t_philo	*p;
	t_data	*d;

	p = (t_philo *)ptr;
	d = p->d;
	ft_print_data(d);
	printf("Debug: Philosopher %d routine started\n", p->philo_id);
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

int	ft_thread_create(t_data *d)
{
	pthread_t	controller;
	int		i;
	int		j;
	int		nbr_of_philos;

	nbr_of_philos = d->nbr_of_philos;

	if (pthread_create(&controller, NULL, &ft_monitoring, d->ps) != 0)
		return (FALSE);
	i = 0;
	while (i < nbr_of_philos)
	{
		printf("Debug: Creating thread for philosopher %d\n", i);
		if (pthread_create(&d->ps[i]->thread_id, NULL, ft_philo_routine,
				d->ps[i]) != 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_detach(d->ps[j]->thread_id);
				j++;
			}
			return (FALSE);
		}
		i++;
	}
	i = 0;
	if (pthread_join(controller, NULL) != 0)
	{
		j = 0;
		while (j < nbr_of_philos)
		{
			pthread_detach(d->ps[j]->thread_id);
			j++;
		}
		return (FALSE);
	}
	while (i < nbr_of_philos)
	{
		printf("Debug: Joining thread for philosopher %d\n", i);
		if (pthread_join(d->ps[i]->thread_id, NULL) != 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_detach(d->ps[j]->thread_id);
				j++;
			}
			return (FALSE);
		}
		i++;
	}
	exit(0);
	return (TRUE);
}
