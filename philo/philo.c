/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:10:57 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/11 19:23:42 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, const char **argv)
{
	t_data		*d;
	t_philo		**ps;
	t_mtx		*fs;
	t_waiter	*w;

	if (!(argc == 5 || argc == 6) || ft_check_argv(argv) == FALSE)
		return (ft_err_exit(NULL, NULL, "Wrong input", 1));
	fs = (t_mtx *)malloc(sizeof(t_mtx) * (int)ft_atos_t_positive(argv[1]));
	if (!fs)
		return (ft_err_exit(NULL, NULL, "Memory allocation error", 1));
	if (ft_init_forks(fs, (int)ft_atos_t_positive(argv[1])) == FALSE)
		return (ft_err_exit(NULL, fs, "Forks initialization error", 1));
	d = (t_data *)malloc(sizeof(t_data));
	if (!d)
		return (ft_err_exit(NULL, fs, "Memory allocation error", 1));
	if (ft_parse_input(argc, argv, d) == FALSE)
		return (ft_err_exit(d, fs, "Input parsing error", 1));
	w = (t_waiter *)malloc(sizeof(t_waiter));
	if (!w)
		return (ft_err_exit(d, fs, "Memory allocation error", 1));
	if (ft_init_waiter(w) == FALSE)
		return (ft_err_exit(d, fs, "Waiter initialization error", 1));
	ps = (t_philo **)malloc(sizeof(t_philo *) * d->nbr_of_philos);
	if (!ps)
		return (ft_err_exit(NULL, NULL, "Memory allocation error", 1));
	d->ps = ps;
	ft_init_philos(d, fs, w, ps);
	ft_assign_time_and_start(ps);
	if (ft_thread_create(ps) == FALSE)
		return (ft_err_exit(d, fs, "Thread creation error", 1));
	if (ft_monitoring((void *)ps) == NULL)
		return (ft_err_exit(d, fs, "Thread monitoring error", 1));
	free(fs);
	ft_free_data(d);
	return (0);
}

