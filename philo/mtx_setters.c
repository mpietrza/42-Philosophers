/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_setters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:46:46 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/13 15:38:31 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_set_time(t_mtx *lock, time_t *value, time_t new_value)
{
	pthread_mutex_lock(lock);
	*value = new_value;
	pthread_mutex_unlock(lock);
}

void	ft_set_val(t_mtx *lock, int *value, int new_value)
{
	pthread_mutex_lock(lock);
	*value = new_value;
	pthread_mutex_unlock(lock);
}

void	ft_set_waiter_state(t_philo *p, int state)
{
	pthread_mutex_lock(p->w->waiter_lock);
	p->w->state = state;
	pthread_mutex_unlock(p->w->waiter_lock);
}

void	ft_fork_mutex_unlock(t_philo *p, int is_fork_l, int is_fork_r)
{
	if (is_fork_l && p->fork_l)
		pthread_mutex_unlock(p->fork_l);
	if (is_fork_r && p->fork_r)
		pthread_mutex_unlock(p->fork_r);
}

