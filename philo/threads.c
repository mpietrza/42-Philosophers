/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:18:01 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/04 15:42:22 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_death_loop(t_philo *p)
{
	int	ret;

	ret = FALSE;
	pthread_mutex_lock(p->death_lock);
	if (*p->is_anyone_dead == TRUE)
		ret = TRUE;
	pthread_mutex_unlock(p->death_lock);
	pthread_mutex_lock(p->full_lock);
	if (*p->are_all_full == TRUE)
		ret = TRUE;
	pthread_mutex_unlock(p->full_lock);
	return (ret);
}

void	*ft_philo_routine(void *ptr)
{
	t_philo	*p;

	p = (t_philo *)ptr;
	while (1)
	{
		ft_eat(p);
		ft_sleep(p);
		ft_think(p);
		if (ft_death_loop(p) == TRUE)
			break ;
	}
	return (ptr);
}


int	ft_thread_create(t_philo **ps)
{
	pthread_t	controller;
	int			i;

	
	if (pthread_create(&controller, NULL, &ft_monitoring, (void *)ps) != 0)
		return (FALSE);
	i = 0;
	while (i < ps[0]->nbr_of_philos)
	{
		if (pthread_create(&ps[i]->philo, NULL, &ft_philo_routine, &ps[i]->philo) != 0)
			return (FALSE);
		i++;
	}
	i = 0;
	while (i < ps[0]->nbr_of_philos)
	{
		ps[i]->when_sim_started = ft_crnt_tm();
		ps[i]->when_was_last_meal = ps[i]->when_sim_started;
		i++;
	}
	if (pthread_join(controller, NULL) != 0)
		return (FALSE);	
	i = 0;
	while (i < ps[0]->nbr_of_philos)
	{
		if (pthread_join(ps[i]->philo, NULL) != 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
