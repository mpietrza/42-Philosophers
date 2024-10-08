/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:08:28 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/08 19:47:22 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_message(char *s, t_philo *p, int id)
{
	size_t	time;
	
	if (p->when_sim_started <= (long long)ft_crnt_tm()) 
		time = ft_crnt_tm() - p->when_sim_started;
	else
	{
		p->when_sim_started = ft_crnt_tm();
		time = 0;    
	}
	if (!ft_death_loop(p))
	{
		pthread_mutex_lock(p->write_lock);
		printf("%zu %d %s\n", time, id, s);
		pthread_mutex_unlock(p->write_lock);
	}
}

void ft_fork_mutex_unlock(t_philo *p, int is_fork_l, int is_fork_r)
{
	if (is_fork_l)
		pthread_mutex_unlock(p->fork_l);
	if (is_fork_r)
		pthread_mutex_unlock(p->fork_r);
}

void	ft_eat(t_philo *p)
{
	if (p->nbr_of_philos == 1)
	{
		if (pthread_mutex_lock(p->fork_r) != 0)
			return ;
		ft_message("has taken a fork", p, p->philo_id);
		ft_usleep(p->tm_t_die);
		pthread_mutex_unlock(p->fork_r);
		return ;
	}
	else if ((p->philo_id) % 2 == 0)
	{
		if (pthread_mutex_lock(p->fork_l) != 0)
			return ;
		ft_message("has taken a fork", p, p->philo_id);
		if (pthread_mutex_lock(p->fork_r) != 0)
			return (ft_fork_mutex_unlock(p, TRUE, FALSE));
	}
	else
	{
		if (pthread_mutex_lock(p->fork_r) != 0)
			return ;
		ft_message("has taken a fork", p, p->philo_id);
		if (pthread_mutex_lock(p->fork_l) != 0)
			return (ft_fork_mutex_unlock(p, FALSE, TRUE));
	}
	ft_message("has taken a fork", p, p->philo_id);
	p->is_eating = TRUE;
	ft_message("is eating", p, p->philo_id);
	if (pthread_mutex_lock(p->meal_lock) != 0)
		return (ft_fork_mutex_unlock(p, TRUE, TRUE));
	p->nbr_of_meals_eaten++;
	pthread_mutex_unlock(p->meal_lock);
	ft_usleep(p->tm_t_eat);	
	if (pthread_mutex_lock(p->meal_lock) != 0)
		return (ft_fork_mutex_unlock(p, TRUE, TRUE));
	p->when_was_last_meal = ft_crnt_tm();	
	p->is_eating = FALSE;
	pthread_mutex_unlock(p->meal_lock);
	ft_fork_mutex_unlock(p, TRUE, TRUE);
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
