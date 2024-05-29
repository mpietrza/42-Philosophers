/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:03:09 by mpietrza          #+#    #+#             */
/*   Updated: 2024/05/28 19:40:46 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	ft_free_data(t_data *d)
{
	if (d)
	{
		if (d->t)
		{
			if (d->t->forks)
				free(d->t->forks);
			if (d->t->philos)
			{
				if (d->t->forks->fork_l)
				{
				//	if (d->t->forks->fork_l->fork)??
					free(fork_l);
				}
				if (d->t->forks->fork_r)
				{
				//	if (d->t->forks->fork_r->fork)??
					free(fork_r);
				}
			free(d->t);
		free(d);
	}
}

t_data	*ft_parse_input(int argc, char **argv)
{
	t_data	*d;
	
	d = (t_data *)malloc(sizeof(t_data));
	if (!d)
		return (NULL);
	d->t = (t_table *)malloc(sizeof(t_table));
	if (!d->t)
	{
		ft_free_data(d);
		return (NULL);
	}
	d->t->nbr_of_philos = ft_atoi_secured(argv[1]);
	d->t->tm_t_die = ft_atoi_secured(argv[2]) * 1000;
	d->t->tm_t_eat = ft_atoi_secured(argv[3]) * 1000;
	d->t->tm_t_sleep = ft_atoi_secured(argv[4]) * 1000;
	if (argc == 6)
		d->t->nbr_of_meals_per_philo = ft_atoi_secured(argv[5]);
	else
		d->t->nbr_of_meals_per_philo = -2;
	d->t->when_simulation_started = 0;
	d->t->is_smltn_going = false;


}
