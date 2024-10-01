/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:31:12 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/01 18:58:54 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
static void ft_print_philo(t_philo *p)
{
	printf("p->thread_id = %lu\n", p->thread_id);
	printf("p->philo_id = %d\n", p->philo_id);
	printf("p->is_eating = %d\n", p->is_eating);
	printf("p->nbr_of_meals_eaten = %d\n", p->nbr_of_meals_eaten);
	printf("p->when_was_last_meal = %ld\n", p->when_was_last_meal);
	printf("p->is_dead = %p\n", (void *)p->is_dead);
	printf("p->fork_l = %p\n", (void *)p->fork_l);
	printf("p->fork_r = %p\n", (void *)p->fork_r);
	printf("p->write_lock = %p\n", (void *)p->write_lock);
	printf("p->death_lock = %p\n", (void *)p->death_lock);
	printf("p->meal_lock = %p\n", (void *)p->meal_lock);
}*/

void ft_print_data(t_data *d)
{
	//int i;

	//i = 0;
	printf("d->nbr_of_philos = %d\n", d->nbr_of_philos);
	printf("d->tm_t_die = %llu\n", d->tm_t_die);
	printf("d->tm_t_eat = %llu\n", d->tm_t_eat);
	printf("d->tm_t_sleep = %llu\n", d->tm_t_sleep);
	printf("d->nbr_of_meals_per_philo = %d\n", d->nbr_of_meals_per_philo);
	printf("d->when_sim_started = %llu\n", d->when_sim_started);
	printf("d->is_dead_flag = %d\n", d->is_dead_flag);
	printf("d->write_lock = %p\n", (void *)&(d->write_lock));
	printf("d->death_lock = %p\n", (void *)&(d->death_lock));
	printf("d->meal_lock = %p\n", (void *)&(d->meal_lock));
	/*while (i < d->nbr_of_philos)
	{
		ft_print_philo(d->ps[i]);
		i++;
	}*/
}

