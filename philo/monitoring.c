/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:30:52 by mpietrza          #+#    #+#             */
/*   Updated: 2024/06/12 18:21:15 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool    ft_is_philo_dead(t_philo *p, size_t time_to_die)
{
        bool	ret;
	
	ret = false;
	pthread_mutex_lock(p->meal_lock);
	if (ft_crnt_tm() - p->when_was_last_meal >= time_to_die
			&& p->is_eating == false)
		ret = true;
	pthread_mutex_unlock(p->meal_lock);
	return (ret);
}

bool    ft_has_anyone_died(t_philo *ps, t_data *d)
{
	size_t	i;

	i = 0;
	while (i < d->nbr_of_philos)
	{
		if (ft_is_philo_dead(&ps[i], d->tm_t_die) == true)
		{
			ft_message("died", &ps[i], &d, ps[i].philo_id);
			pthread_mutex_lock(d->death_lock);
			d->is_dead_flag = true;
			pthread_mutex_unlock(d->death_lock);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	ft_have_all_eaten(t_philo *ps)
{
	size_t	i;
	size_t	has_eaten_all;

	i = 0;
	has_eaten_all = 0;
	if (d->nbr_of_meals_per_philo == -2)
		return (false);
	while (i < d->nbr_of_philos)
	{
		pthread_mutex_lock(d->meal_lock);
		if (ps[i].nbr_of_meals_eaten >= d->nbr_of_meals_per_philo)
			has_eaten_all++;
		pthread_mutex_unlock(d->meal_lock);
		i++;
	}
	if (has_eaten_all == d->nbr_of_philos)
	{
		pthread_mutex_lock(d->death_lock);
		d->is_dead_flag = true;
		pthread_mutex_unlock(d->death_lock);
		return (true);
	}
	return (false);
}

void	*ft_monitoring(void *ptr)
{
	t_philo *ps;

	ps = (t_philo *)ptr;
	while (1)
		if (ft_has_anyone_died(ps) == true
				|| ft_have_all_eaten(ps) == true)
			break;
	return (ptr);
}
