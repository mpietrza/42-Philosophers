/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:31:12 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/08 17:50:03 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_print_data(t_data *d)
{
	printf("d->nbr_of_philos = %d\n", d->nbr_of_philos);
	printf("d->is_anyone_dead_flag = %d\n", d->is_anyone_dead_flag);
	printf("d->write_lock = %p\n", (void *)&(d->write_lock));
	printf("d->death_lock = %p\n", (void *)&(d->death_lock));
	printf("d->meal_lock = %p\n", (void *)&(d->meal_lock));
}

