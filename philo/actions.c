/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:08:28 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/02 21:21:39 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_message(char *s, t_philo *p, int id)
{
	unsigned long long	time;

	pthread_mutex_lock(p->write_lock);
	time = ft_crnt_tm() - p->when_sim_started;
	if (!ft_death_loop(p))
		printf("%llu %d %s\n", time, id, s);
	pthread_mutex_unlock(p->write_lock);
}

void	ft_eat(t_philo *p)
{
    int ret;

    // Always lock the lower-numbered fork first to avoid deadlock
    if ((p->philo_id - 1) % 2 == 0)
    {
        ret = pthread_mutex_lock(p->fork_l);
        if (ret != 0) 
			return ; // Handle error
        ft_message("has taken a fork", p, p->philo_id);
        ret = pthread_mutex_lock(p->fork_r);
        if (ret != 0) 
        {
            pthread_mutex_unlock(p->fork_l);
            return; // Handle error
        }
    }
    else
    {
        ret = pthread_mutex_lock(p->fork_r);
        if (ret != 0)
			return; // Handle error
        ft_message("has taken a fork", p, p->philo_id);
        ret = pthread_mutex_lock(p->fork_l);
        if (ret != 0) 
        {
            pthread_mutex_unlock(p->fork_r); 
            return; // Handle error
        }
    }
    ft_message("has taken a fork", p, p->philo_id);
    p->is_eating = TRUE;
    ft_message("is eating", p, p->philo_id);
    ret = pthread_mutex_lock(p->meal_lock);
    if (ret != 0) 
    {
        // Handle error
        pthread_mutex_unlock(p->fork_l);
        pthread_mutex_unlock(p->fork_r);
        return;
    }
	ft_usleep(p->tm_t_eat);
    p->when_was_last_meal = ft_crnt_tm();
    p->nbr_of_meals_eaten++;
    pthread_mutex_unlock(p->meal_lock);
    
    p->is_eating = FALSE;
    pthread_mutex_unlock(p->fork_l);
    pthread_mutex_unlock(p->fork_r);
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
