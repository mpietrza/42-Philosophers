/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milosz <milosz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:33:19 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/15 17:07:52 by milosz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_parse_input(int argc, const char **argv, t_data *d)
{
	d->argv = argv;
	d->argc = argc;
	d->nbr_of_philos = (int)ft_atos_t_positive(argv[1]);
	pthread_mutex_init(&d->write_lock, NULL);
	pthread_mutex_init(&d->meal_lock, NULL);
	d->atoi_errno = 0;
	d->msg_counter = 0;
	d->msg_time[0] = -1;
	d->msg[0] = -1;
	d->msg_id[0] = -1;
	d->is_first_message = TRUE;
	d->is_last_message = FALSE;
	return (TRUE);
}

void ft_parse_philo(t_data *d, t_philo *p)
{
	p->nbr_of_philos = d->nbr_of_philos;
	p->when_was_last_meal = ft_crnt_tm();
	p->tm_t_die = (time_t)ft_atos_t_positive(d->argv[2]);
	p->tm_t_eat = (time_t)ft_atos_t_positive(d->argv[3]);
	p->tm_t_sleep = (unsigned long long)ft_atos_t_positive(d->argv[4]);
	if (d->argc == 6)
		p->nbr_of_meals_per_philo = (int)ft_atos_t_positive(d->argv[5]);
	else
		p->nbr_of_meals_per_philo = -1;
	p->write_lock = &d->write_lock;
	p->meal_lock = &d->meal_lock;
	p->is_eating = FALSE;
	p->nbr_of_meals_eaten = 0;
}
