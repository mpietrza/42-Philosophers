/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:08:28 by mpietrza          #+#    #+#             */
/*   Updated: 2024/06/06 16:54:57 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_message(char *s, t_philo *p, t_data *d, int id)
{
	size_t	time;

	pthread_mutex_lock(p->write_lock);
	time = ft_crnt_tm() - d->when_sim_started;
	if (!death_loop(p))
		printf("%zu %d %s\n", time, id, s);
	pthread_mutex_unlock(p->write_lock);
}

void	ft_eat(t_philo *p, t_data *d)
{
	pthread_mutex_lock(p->fork_r);
	ft_message("has taken a fork", p, p->philo_id);
	if (p->nbr_of_philos == 1)
	{
		ft_usleep(d->tm_t_die);
		pthread_mutex_unlock(p->fork_r);
		return ;
	}
	pthread_mutex_lock(p->fork_l);
	ft_message("has taken a fork", p, p->philo_id);
	p->is_eating = true;
	ft_message("is eating", p, p->philo_id);
	pthread_mutex_lock(p->meal_lock);
	p->when_was_last_meal = ft_crnt_tm();
	p->nbr_of_meals_eaten++;
	pthread_mutex_unlock(p->meal_lock);
	ft_usleep(p->tm_t_eat);
	p->is_eating = false;
	pthread_mutex_unlock(p->fork_l);
	pthread_mutex_unlock(p->fork_r);
}

void	ft_sleep(t_philo *p, t_data *d)
{
	ft_message("is sleeping", p, p->philo_id);
	ft_usleep(d->tm_t_sleep);
}


void	ft_think(t_philo *p)
{
	ft_message("is thinking", p, p->philo_id);i
}
