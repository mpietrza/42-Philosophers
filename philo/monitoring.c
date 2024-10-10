/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milosz <milosz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:30:52 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/10 22:54:09 by milosz           ###   ########.fr       */
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

static void	print_msg_and_free(t_philo *p, size_t *msg_nbr_prev)
{
	pthread_mutex_lock(p->write_lock);
	if (p->d->msg_nbr != *msg_nbr_prev)
	{
		*msg_nbr_prev = p->d->msg_nbr;
		write(1, p->d->msg, ft_strlen(p->d->msg));
		write(1, "\n", 1);
		free(p->d->msg);
	}
	pthread_mutex_unlock(p->write_lock);	
}

void	*ft_monitoring(void *ptr)
{
	t_philo	**ps;
	size_t	msg_nbr_prev;
	
	ps = (t_philo **)ptr;
	while (1)
	{
		if (ft_has_anyone_died(ps) == TRUE)
		{
			ft_message("\033[1;31mdied\033[0m", *ps, ps[0]->philo_id);
			print_msg_and_free(ps[0], &msg_nbr_prev);
			break ;
		}
		if (ps[0]->nbr_of_meals_per_philo != -1)
		{
			if (ft_have_all_eaten(ps) == ps[0]->nbr_of_philos)
				break ;
		}
		print_msg_and_free(ps[0], &msg_nbr_prev);
	}
	//ft_set_waiter_state(ps[0], CLEANING);
	return (ptr);
}
