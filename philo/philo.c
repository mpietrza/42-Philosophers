/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milosz <milosz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:10:57 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/15 17:37:12 by milosz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	ft_assign_time_and_start(t_philo **ps)
{
	int	i;

	i = 0;
	*ps[0]->when_sim_started = ft_crnt_tm();
	while (i < ps[0]->nbr_of_philos)
	{
		pthread_mutex_lock(ps[i]->meal_lock);
		ps[i]->when_was_last_meal = *ps[0]->when_sim_started;
		pthread_mutex_unlock(ps[i]->meal_lock);
		i++;
	}
	pthread_mutex_lock(ps[0]->w->waiter_lock);
	ps[0]->w->state = SERVING;
	pthread_mutex_unlock(ps[0]->w->waiter_lock);
}

int	main(int argc, const char **argv)
{
	t_mtx		*fs;
	t_wtr	*w;
	t_data		*d;
	t_philo		**ps;

	if (ft_check_arg(argc, argv) == FALSE)
		return (ft_err_exit(NULL, NULL, NULL, "Wrong input"));
	fs = ft_init_forks((int)ft_atos_t_positive(argv[1]));
	if (!fs)
		return (ft_err_exit(NULL, NULL, NULL, "Memory allocation error"));
	w = ft_init_wtr();
	if (!w)
		return (ft_err_exit(NULL, fs, NULL, "Waiter initialization error"));
	d = ft_init_data(argc, argv);
	if (!d)
		return (ft_err_exit(NULL, fs, w, "Data initialization error"));
	ps = ft_init_philos(d, fs, w);
	if (!ps)
		return (ft_err_exit(d, fs, w, "Philo initialization error"));
	ft_assign_time_and_start(ps);
	if (ft_thread_create(ps) == FALSE)
		return (ft_err_exit(d, fs, w, "Thread creation error"));
	if (ft_monitoring((void *)ps) == NULL)
		return (ft_err_exit(d, fs, w, "Thread monitoring error"));
	return (ft_exit_success(d, fs, w));
}


