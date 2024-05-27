/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:08:28 by mpietrza          #+#    #+#             */
/*   Updated: 2024/05/24 17:33:46 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	w_status(char *s, t_data *d, t_mutex *m, int i)
{
	long	time;

	pthread_mutex_lock(&m->mutex_msg);
	time = crnt_tm() - d->s_time;
	if (i <= d->nbr_of_philos && check_meals(d) == 0 && d->is_smltn_on == 1)
		printf("%ld %d %s\n", time, i, s);
	pthread_mutex_unlock(&m->mutex_msg);
}

void	ft_take_fork(t_data *d, t_mutex *m, int i)
{
	pthread_mutex_lock(&m->mutex[d->nbr_of_philos[i].fork_r]);
	w_status("has taken a fork\n", d, i + 1);
	//...
}

void	ft_eat(t_data *d, t_mutex *m, int i)
{
	w_status("is eating\n", d, m, i + 1);
	d->philo[i].num_o_meals++;
	//..
}

void	ft_sleep(t_data *d, t_mutex *m, int i)
{
	w_status("is sleeping\n", d, m, i + 1);
	ft_usleep(d->tm_t_sleep);
	w_status("is thinking\n", d, m, i + 1);
