/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:08:28 by mpietrza          #+#    #+#             */
/*   Updated: 2024/06/12 19:03:41 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_message(char *s, t_philo *p, t_data *d, int id)
{
	size_t	time;

	pthread_mutex_lock(p->write_lock);
	time = ft_crnt_tm() - d->when_sim_started;
	if (!ft_death_loop(p, d))
		printf("%zu %d %s\n", time, id, s);
	pthread_mutex_unlock(p->write_lock);
}

void	ft_eat(t_philo *p, t_data *d)
{
	pthread_mutex_lock(p->fork_r);
	ft_message("has taken a fork", p, d, p->philo_id);
	if (d->nbr_of_philos == 1)
	{
		ft_usleep(d->tm_t_die);
		pthread_mutex_unlock(p->fork_r);
		return ;
	}
	pthread_mutex_lock(p->fork_l);
	ft_message("has taken a fork", p, d, p->philo_id);
	p->is_eating = true;
	ft_message("is eating", p, d, p->philo_id);
	pthread_mutex_lock(p->meal_lock);
	p->when_was_last_meal = ft_crnt_tm();
	p->nbr_of_meals_eaten++;
	pthread_mutex_unlock(p->meal_lock);
	ft_usleep(d->tm_t_eat);
	p->is_eating = false;
	pthread_mutex_unlock(p->fork_l);
	pthread_mutex_unlock(p->fork_r);
}

void	ft_sleep(t_philo *p, t_data *d)
{
	ft_message("is sleeping", p, d, p->philo_id);
	ft_usleep(d->tm_t_sleep);
}


void	ft_think(t_philo *p, t_data *d)
{
	ft_message("is thinking", p, d, p->philo_id);
}
