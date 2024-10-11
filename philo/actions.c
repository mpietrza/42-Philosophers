/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:08:28 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/11 19:17:44 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_message(int msg, t_philo *p, int id)
{
	pthread_mutex_lock(p->write_lock);
	p->d->msg_id = id;
	p->d->msg = msg;
	p->d->msg_counter++;
	pthread_mutex_unlock(p->write_lock);
	usleep(10);
}

void ft_fork_mutex_unlock(t_philo *p, int is_fork_l, int is_fork_r)
{
	if (is_fork_l && p->fork_l)
		pthread_mutex_unlock(p->fork_l);
	if (is_fork_r && p->fork_r)
		pthread_mutex_unlock(p->fork_r);
}

static void ft_one_philo(t_philo *p)
{
	if (pthread_mutex_lock(p->fork_r) != 0)
		return ;
	ft_message(TAKEN_FORK, p, p->philo_id);
	ft_usleep(p->tm_t_die);
	pthread_mutex_unlock(p->fork_r);
}

static int	ft_increment_meal_counter(t_philo *p)
{
	if (pthread_mutex_lock(p->meal_lock) != 0)
	{
		ft_fork_mutex_unlock(p, TRUE, TRUE);
		return (FALSE);
	}
	p->is_eating = TRUE;
	p->nbr_of_meals_eaten++;
	pthread_mutex_unlock(p->meal_lock);
	return (TRUE);
}

static int ft_update_last_meal_time_and_change_is_eating(t_philo *p)
{
	if (pthread_mutex_lock(p->meal_lock) != 0)
	{
		ft_fork_mutex_unlock(p, TRUE, TRUE);
		return (FALSE);
	}
	p->when_was_last_meal = ft_crnt_tm();	
	p->is_eating = FALSE;
	pthread_mutex_unlock(p->meal_lock);
	return (TRUE);
}

static int ft_take_forks(t_philo *p, int lr_or_rl)
{
	if (lr_or_rl == LEFT_RIGHT)
	{
		if (pthread_mutex_lock(p->fork_l) != 0)
			return (FALSE);
		ft_message(TAKEN_FORK, p, p->philo_id);
		if (pthread_mutex_lock(p->fork_r) != 0)
		{
			ft_fork_mutex_unlock(p, TRUE, FALSE);
			return (FALSE);
		}
	}
	else if (lr_or_rl == RIGHT_LEFT)
	{
		if (pthread_mutex_lock(p->fork_r) != 0)
			return (FALSE);
		ft_message(TAKEN_FORK, p, p->philo_id);
		if (pthread_mutex_lock(p->fork_l) != 0)
		{
			ft_fork_mutex_unlock(p, FALSE, TRUE);
			return (FALSE);
		}
	}
	else
		return (FALSE);
	return (TRUE);
}

int	ft_eat(t_philo *p)
{
	if (ft_get_waiter_state(p) != SERVING)
		return (FALSE);
	if (p->nbr_of_philos == 1)
	{
		ft_one_philo(p);
		return (TRUE);
	}
	else if ((p->philo_id) % 2 == 0)
	{
		if (ft_take_forks(p, LEFT_RIGHT) == FALSE)
			return (FALSE);
	}
	else
		if (ft_take_forks(p, RIGHT_LEFT) == FALSE)
			return (FALSE);
	ft_message(TAKEN_FORK, p, p->philo_id);
	ft_message(EATING, p, p->philo_id);
	if (ft_increment_meal_counter(p) == FALSE)
		return (FALSE);
	ft_usleep(p->tm_t_eat);		
	if (ft_update_last_meal_time_and_change_is_eating(p) == FALSE)
		return (FALSE);
	ft_fork_mutex_unlock(p, TRUE, TRUE);
	return (TRUE);
}


int	ft_sleep(t_philo *p)
{
	if (ft_get_waiter_state(p) != SERVING)
		return (FALSE);
	ft_message(SLEEPING, p, p->philo_id);
	ft_usleep(p->tm_t_sleep);
	return (TRUE);
}

int	ft_think(t_philo *p)
{
	if (ft_get_waiter_state(p) != SERVING)
		return (FALSE);
	ft_message(THINKING, p, p->philo_id);
		return (TRUE);
}

