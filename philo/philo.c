/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:10:57 by mpietrza          #+#    #+#             */
/*   Updated: 2024/06/13 16:59:34 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, const char **argv)
{
	t_data	*d;
	t_mtx	*fs;
	t_philo	*ps;

	if (!(argc == 5 || argc == 6) || ft_check_argv(argv) == false)
	{
		printf("Error!\nWrong input\n");
		return (1);
	}
	d = ft_parse_input(argc, argv);
	if (!d)
	{
		printf("Error!\nMemory allocation error\n");
		return (1);
	}
	printf("d = %p\n", d);
	fs = (t_mtx *)malloc(sizeof(t_mtx) * d->nbr_of_philos);
	if (!fs)
	{
		ft_err_exit(d, "Memory allocation error");
		return (1);
	}
	if (ft_init_forks(fs, d) == false)
		return (1);
	ps = (ft_init_philos(d, fs));
	printf("ps[0].d = %p\n", ps[0].d);
	if (!ps)
		return (1);
	d->ps = ps;
	d->when_sim_started = ft_crnt_tm();
	if (ft_thread_create(d) == false)
		return (1);
	ft_free_data(d);
	return (0);
}
