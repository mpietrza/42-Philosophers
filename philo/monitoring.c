/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:30:52 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/13 16:59:02 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    ft_has_anyone_died(t_philo **ps)
{
	int	i;

	i = 0;
	while (i < ps[0]->nbr_of_philos)
	{
		if ((ft_crnt_tm() - ft_get_time(ps[i]->meal_lock,
				&ps[i]->when_was_last_meal) >= ps[0]->tm_t_die)
					&& ft_get_val(ps[i]->meal_lock, &ps[i]->is_eating) == FALSE)
		{
			pthread_mutex_lock(ps[0]->write_lock);
			if (ps[i]->d->is_last_message == FALSE)
				printf("\033[1;31m%ld %d died\033[0m\n",
					ft_crnt_tm() - *ps[i]->when_sim_started, ps[i]->philo_id);
			ps[i]->d->is_last_message = TRUE;
			pthread_mutex_unlock(ps[0]->write_lock);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

static void ft_increment_finished_eating_counter(t_philo *p,
	int *finished_eating)
{
	pthread_mutex_lock(p->meal_lock);
	if (p->nbr_of_meals_eaten >= p->nbr_of_meals_per_philo)
		(*finished_eating)++;
	pthread_mutex_unlock(p->meal_lock);
}

int ft_have_all_eaten(t_philo **ps)
{
	int i;
	int finished_eating;

	if (!ps)
		return (FALSE);
	i = 0;
	finished_eating = 0;
	while (i < ps[0]->nbr_of_philos)
	{
		ft_increment_finished_eating_counter(ps[i], &finished_eating);
		i++;
	}
	return (finished_eating);
}

void	*ft_monitoring(void *ptr)
{
	t_philo	**ps;
	size_t	msg_counter_prev;
	
	ps = (t_philo **)ptr;
	while (1)
	{
		if (ft_has_anyone_died(ps) == TRUE)
		{
			ft_set_waiter_state(ps[0], CLEANING);
			break ;
		}
		if (ps[0]->nbr_of_meals_per_philo != -1)
		{
			
			if (ft_have_all_eaten(ps) == ps[0]->nbr_of_philos)
			{	
				ft_set_waiter_state(ps[0], CLEANING);
				break ;
			}
		}
		ft_get_msg_and_print(ps[0], &msg_counter_prev);
	}
	return (ptr);
}
