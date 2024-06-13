/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:30:52 by mpietrza          #+#    #+#             */
/*   Updated: 2024/06/13 16:26:53 by mpietrza         ###   ########.fr       */
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
	printf("Debug 1\n");
	printf("nbr_of_philos = %zu\n", d->nbr_of_philos);
	while (i < d->nbr_of_philos)
	{
		printf("Debug 2.%zu\n", i);
		if (ft_is_philo_dead(&ps[i], d->tm_t_die) == true)
		{
			printf("Debug 2.%zu.dead\n", i);
			ft_message("died", &ps[i], d, ps[i].philo_id);
			pthread_mutex_lock(&d->death_lock);
			d->is_dead_flag = true;
			pthread_mutex_unlock(&d->death_lock);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	ft_have_all_eaten(t_philo *ps, t_data *d)
{
	size_t	i;
	size_t	has_eaten_all;

	i = 0;
	has_eaten_all = 0;
	if ((int)d->nbr_of_meals_per_philo == -2)
		return (false);
	while (i < d->nbr_of_philos)
	{
		pthread_mutex_lock(&d->meal_lock);
		if (ps[i].nbr_of_meals_eaten >= d->nbr_of_meals_per_philo)
			has_eaten_all++;
		pthread_mutex_unlock(&d->meal_lock);
		i++;
	}
	if (has_eaten_all == d->nbr_of_philos)
	{
		pthread_mutex_lock(&d->death_lock);
		d->is_dead_flag = true;
		pthread_mutex_unlock(&d->death_lock);
		return (true);
	}
	return (false);
}

void	*ft_monitoring(void *ptr)
{
	t_philo *ps;
	t_data	*d;

	ps = (t_philo *)ptr;
	printf("Debug_monitoring1\n");
	printf("Debug: ps address = %p, ps[0].d address = %p\n", (void *)ps, (void *)ps[0].d);
	d = ps[0].d;
	printf("nbr of philos = %zu\n", d->nbr_of_philos);
	while (1)
	{
		if (ft_has_anyone_died(ps, d) == true
				|| ft_have_all_eaten(ps, d) == true)
			break;
		usleep(1000);
	}
	return (ptr);
}
