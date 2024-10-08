/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:30:52 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/08 19:41:54 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    ft_is_philo_dead(t_philo *p)
{
	pthread_mutex_lock(p->meal_lock);
	if ((time_t)(ft_crnt_tm() - p->when_was_last_meal) >= p->tm_t_die
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
	//	ft_usleep(100);
		if (ft_is_philo_dead(ps[i]) == TRUE)
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
		if (ps[i]->nbr_of_meals_eaten >= ps[i]->nbr_of_meals_per_philo)
			finished_eating++;
		pthread_mutex_unlock(ps[i]->meal_lock);
		//printf("ps[%d]->nbr_of_meals_eaten = %d\n", i, ps[i]->nbr_of_meals_eaten);
		ft_usleep(5);
		i++;
	}
	//printf("finished_eating = %d\n", finished_eating);
	return (finished_eating);
}

void	*ft_monitoring(void *ptr)
{
	t_philo	**ps;
	
	ps = (t_philo **)ptr;
	while (1)
	{
		if (ft_has_anyone_died(ps) == TRUE)
			break ;
		else if (ps[0]->nbr_of_meals_per_philo > 0)
			if (ft_have_all_eaten(ps) == ps[0]->nbr_of_philos)
			{
				pthread_mutex_lock(ps[0]->full_lock);
				*ps[0]->are_all_full = TRUE;
				pthread_mutex_unlock(ps[0]->full_lock);
				break ;
			}
	}
	return (ptr);
}
