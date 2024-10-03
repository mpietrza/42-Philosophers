/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:08:28 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/03 17:50:14 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_message(char *s, t_philo *p, int id)
{
	unsigned long long	time;

	pthread_mutex_lock(p->write_lock);
	if (p->when_sim_started <= (long long)ft_crnt_tm()) 
		time = ft_crnt_tm() - p->when_sim_started;
	else
	{
		p->when_sim_started = ft_crnt_tm();
		time = 0;    
	}
	if (!ft_death_loop(p))
		printf("%llu %d %s\n", time, id, s);
	pthread_mutex_unlock(p->write_lock);
}

void ft_fork_mutex_unclock(t_philo *p, int is_fork_l, int is_fork_r)
{
	if (is_fork_l)
		pthread_mutex_unlock(p->fork_l);
	if (is_fork_r)
		pthread_mutex_unlock(p->fork_r);
}

void	ft_eat(t_philo *p)
{
	if ((p->philo_id) % 2 == 0)
	{
		if (pthread_mutex_lock(p->fork_l) != 0)
			return ;
		ft_message("has taken a fork", p, p->philo_id);
		if (pthread_mutex_lock(p->fork_r) != 0)
			return (ft_fork_mutex_unclock(p, TRUE, FALSE));
	}
	else
	{
		if (pthread_mutex_lock(p->fork_r) != 0)
			return ;
		ft_message("has taken a fork", p, p->philo_id);
		if (pthread_mutex_lock(p->fork_l) != 0)
			return (ft_fork_mutex_unclock(p, FALSE, TRUE));
	}
	ft_message("has taken a fork", p, p->philo_id);
	if (pthread_mutex_lock(p->meal_lock) != 0)
		return (ft_fork_mutex_unclock(p, TRUE, TRUE));
	p->is_eating = TRUE;
	pthread_mutex_unlock(p->meal_lock);
	ft_message("is eating", p, p->philo_id);
	ft_usleep(p->tm_t_eat);
	p->when_was_last_meal = ft_crnt_tm();
	p->nbr_of_meals_eaten++;
	if (pthread_mutex_lock(p->meal_lock) != 0)
		return (ft_fork_mutex_unclock(p, TRUE, TRUE));
	p->is_eating = FALSE;
	pthread_mutex_unlock(p->meal_lock);
	ft_fork_mutex_unclock(p, TRUE, TRUE);
}

void	ft_sleep(t_philo *p)
{
	ft_message("is sleeping", p, p->philo_id);
	ft_usleep(p->tm_t_sleep);
}


void	ft_think(t_philo *p)
{
	ft_message("is thinking", p, p->philo_id);
}
