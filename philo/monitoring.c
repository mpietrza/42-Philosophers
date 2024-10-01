/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:30:52 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/01 18:21:34 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    ft_is_philo_dead(t_philo *p, size_t time_to_die)
{
        int	ret;
	
	ret = FALSE;
	pthread_mutex_lock(p->meal_lock);
	if (ft_crnt_tm() - p->when_was_last_meal >= time_to_die
			&& p->is_eating == FALSE && !p->d->is_dead_flag)
		ret = TRUE;
	pthread_mutex_unlock(p->meal_lock);
	return (ret);
}

int    ft_has_anyone_died(t_data *d)
{
	int	i;

	i = 0;
	printf("Debug \"has anyone died\"\n");
	if (d) 
	{
		
		while (i < d->nbr_of_philos)
		{
			pthread_mutex_lock(&d->death_lock);
			if (d->is_dead_flag)
			{
				pthread_mutex_unlock(&d->death_lock);
				return (TRUE);
			}
			pthread_mutex_unlock(&d->death_lock);

			printf("Debug 2.%d\n", i);
			if (ft_is_philo_dead(d->ps[i], d->tm_t_die) == TRUE)
			{
				printf("Debug 2.%d.dead\n", i);
				ft_message("died", d->ps[i], d, d->ps[i]->philo_id);
				pthread_mutex_lock(&d->death_lock);
				d->is_dead_flag = TRUE;
				pthread_mutex_unlock(&d->death_lock);
				return (TRUE);
			}
			i++;
		}
	}
	else
		exit(1);
	return (FALSE);
}

int	ft_have_all_eaten(t_data *d)
{
	int	i;
	int	has_eaten_all;

	if (!d)
		return (FALSE);
	i = 0;
	has_eaten_all = 0;
	printf("d->nbr_of_meals_per_philo = %d\n", d->nbr_of_meals_per_philo);
	if (d && d->nbr_of_meals_per_philo == -2)
		return (FALSE);
	ft_print_data(d);
	while (d && i < d->nbr_of_philos - 1)
	{
		pthread_mutex_lock(&d->meal_lock);
		if (d->ps[i]->nbr_of_meals_eaten >= d->nbr_of_meals_per_philo)
			has_eaten_all++;
		pthread_mutex_unlock(&d->meal_lock);
		i++;
	}
	if (has_eaten_all == d->nbr_of_philos)
	{
		pthread_mutex_lock(&d->death_lock);
		d->is_dead_flag = TRUE;
		pthread_mutex_unlock(&d->death_lock);
		return (TRUE);
	}
	return (FALSE);
}

void	*ft_monitoring(void *ptr)
{
	t_data	*d = (t_data *)ptr;

	printf("Debug: Monitoring started\n");
	ft_print_data(d);
	while (1)
	{
		pthread_mutex_lock(&d->death_lock);
		if (d->is_dead_flag)
		{
			pthread_mutex_unlock(&d->death_lock);
			break ;
		}
		pthread_mutex_unlock(&d->death_lock);
		if (ft_has_anyone_died(d) || ft_have_all_eaten(d))
			break ;
	}
	return (ptr);
}
