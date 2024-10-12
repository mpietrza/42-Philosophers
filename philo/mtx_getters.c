/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_getters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milosz <milosz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:37:45 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/12 18:20:34 by milosz           ###   ########.fr       */
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

/*int ft_get_msg(t_philo *p)
{
	int		msg;

	pthread_mutex_lock(p->write_lock);
	msg = p->d->msg;
	pthread_mutex_unlock(p->write_lock);
	return (msg);
}*/

void	ft_get_msg_and_print(t_philo *p, size_t *msg_counter_prev)
{
	int i;

	i = 0;
	pthread_mutex_lock(p->write_lock);
	i = *msg_counter_prev;
	if (p->d->msg_counter != *msg_counter_prev)
	{
		while (i < (int)p->d->msg_counter)
		{
			printf("i = %d\n", i);
			if (p->d->msg[i] == TAKEN_FORK)
				printf("%ld %d has taken a fork\n", ft_crnt_tm() - *p->when_sim_started, p->d->msg_id[i]);
			else if (p->d->msg[i] == EATING)
				printf("%ld %d is eating\n", ft_crnt_tm() - *p->when_sim_started, p->d->msg_id[i]);
			else if (p->d->msg[i] == SLEEPING)
				printf("%ld %d is sleeping\n", ft_crnt_tm() - *p->when_sim_started, p->d->msg_id[i]);
			else if (p->d->msg[i] == THINKING)
				printf("%ld %d is thinking\n", ft_crnt_tm() - *p->when_sim_started, p->d->msg_id[i]);
			/*else if (p->d->msg[i] == DIED)
				printf("%ld %d died\n", ft_crnt_tm() - *p->when_sim_started, p->d->msg_id);*/
			i++;
		}
	}
	*msg_counter_prev = p->d->msg_counter;
	pthread_mutex_unlock(p->write_lock);
}
