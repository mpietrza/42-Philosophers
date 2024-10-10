/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:30:52 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/10 16:25:20 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    ft_has_anyone_died(t_philo **ps)
{
	int	i;

	i = 0;
	while (i < ps[0]->nbr_of_philos)
	{
		if ((ft_crnt_tm() - ft_get_when_was_last_meal(ps[i]) >= ps[0]->tm_t_die)
			&& ft_get_is_eating(ps[i]) == FALSE)
		{
			ft_message("\033[1;31mdied\033[0m", *ps, ps[i]->philo_id);
			ft_set_waiter_state(ps[0], CLEANING);
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
	
	ps = (t_philo **)ptr;
	while (1)
	{
		if (ft_has_anyone_died(ps) == TRUE)
			break ;
		if (ps[0]->nbr_of_meals_per_philo != -1)
		{
			if (ft_have_all_eaten(ps) == ps[0]->nbr_of_philos)
				break ;
		}
		pthread_mutex_lock(ps[0]->write_lock);
		printf("%zu %d %s\n", time, id, s);
		pthread_mutex_unlock(ps[0]->write_lock);
		usleep(100); // Add a small delay to reduce CPU usage
	}
	ft_set_waiter_state(ps[0], CLEANING);
	return (ptr);
}
