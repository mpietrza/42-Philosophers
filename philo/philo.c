/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:10:57 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/08 18:31:10 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, const char **argv)
{
	t_data	*d;
	t_philo	**ps;
	t_mtx	*fs;
	int	nbr_of_philos;

	if (!(argc == 5 || argc == 6) || ft_check_argv(argv) == FALSE)
		return (ft_err_exit(NULL, NULL, "Wrong input", 1));
	nbr_of_philos = (int)ft_atos_t_positive(argv[1]);
	fs = (t_mtx *)malloc(sizeof(t_mtx) * nbr_of_philos);
	if (!fs)
		return (ft_err_exit(NULL, NULL, "Memory allocation error", 1));
	if (ft_init_forks(fs, nbr_of_philos) == FALSE)
		return (ft_err_exit(NULL, fs, "Forks initialization error", 1));
	d = (t_data *)malloc(sizeof(t_data));
	if (!d)
		return (ft_err_exit(NULL, fs, "Memory allocation error", 1));
	ft_parse_input(argc, argv, d);
	ps = (t_philo **)malloc(sizeof(t_philo *) * d->nbr_of_philos);
	if (!ps)
		return (ft_err_exit(NULL, NULL, "Memory allocation error", 1));
	d->ps = ps;
	ft_init_philos(d, fs, ps);
	if (ft_thread_create(ps) == FALSE)
		return (ft_err_exit(d, fs, "Thread creation error", 1));
	if (ft_monitoring((void *)ps) == NULL)
		return (ft_err_exit(d, fs, "Thread monitoring error", 1));
	free(fs);
	ft_free_data(d);
	return (0);
}

