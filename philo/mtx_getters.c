/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_getters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:37:45 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/09 18:12:01 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_get_waiter_state(t_philo *p)
{
	int	state;

	pthread_mutex_lock(p->w->waiter_lock);
	state = p->w->state;
	pthread_mutex_unlock(p->w->waiter_lock);
	return (state);
}

time_t	ft_get_when_was_last_meal(t_philo *p)
{
	time_t	when_was_last_meal;
	
	pthread_mutex_lock(p->meal_lock);
	when_was_last_meal = p->when_was_last_meal;
	pthread_mutex_unlock(p->meal_lock);
	return (when_was_last_meal);
}

int ft_get_is_eating(t_philo *p)
{
	int	is_eating;

	pthread_mutex_lock(p->meal_lock);
	is_eating = p->is_eating;
	pthread_mutex_unlock(p->meal_lock);
	return (is_eating);
}
