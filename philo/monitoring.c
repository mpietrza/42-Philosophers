/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:30:52 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/04 16:08:16 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    ft_is_philo_dead(t_philo *p, size_t time_to_die)
{
	ft_usleep(1);
	pthread_mutex_lock(p->meal_lock);

	if (ft_crnt_tm() - p->when_was_last_meal >= time_to_die
			&& p->is_eating == FALSE)
	{
		pthread_mutex_unlock(p->meal_lock);
		return (TRUE);
	}
	pthread_mutex_unlock(p->meal_lock);
	
	return (FALSE);
}

int    ft_has_anyone_died(t_philo **ps)
{
	int	i;

	i = 0;
	while (i < ps[0]->nbr_of_philos)
	{
		if (ft_is_philo_dead(ps[i], ps[i]->tm_t_die) == TRUE)
		{
			ft_message("died", *ps, ps[i]->philo_id);
			pthread_mutex_lock(ps[i]->death_lock);
			*ps[i]->is_anyone_dead = TRUE;
			pthread_mutex_unlock(ps[i]->death_lock);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
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
		pthread_mutex_lock(ps[i]->meal_lock);
		if (ps[i]->nbr_of_meals_eaten >= ps[0]->nbr_of_meals_per_philo
				&& ps[i]->is_eating == FALSE)
			finished_eating++;
		pthread_mutex_unlock(ps[i]->meal_lock);
		i++;
	}
	if (finished_eating == ps[0]->nbr_of_philos)
	{
		pthread_mutex_lock(ps[0]->full_lock);
		*(ps[0])->are_all_full = TRUE;
		pthread_mutex_unlock(ps[0]->full_lock);
		return (TRUE);
	}
	return (FALSE);
}

void	*ft_monitoring(void *ptr)
{
	t_philo	**ps;
	
	ps = (t_philo **)ptr;
	while (1)
	{
		if (ft_has_anyone_died(ps) == TRUE)
			break ;
		else if (ps[0]->nbr_of_meals_per_philo != -1)
			if (ft_have_all_eaten(ps) == TRUE)
				break ;
	}
	return (ptr);
}
