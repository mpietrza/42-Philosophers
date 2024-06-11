/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:10:57 by mpietrza          #+#    #+#             */
/*   Updated: 2024/06/11 16:06:08 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	d;

	if (!(argc == 5 || argc == 6) || ft_check_argv(argv) == false)
		return (1);
	d = ft_prase_input(argc, argv);
	if (!d)
		return (write(2, "Memory allocation error\n", 25), 1);
	ft_init_forks(fs, d->nbr_of_philos);
	ft_init_philos(ps, &d, fs, argv);
	thread_create(&d, fs);
	ft_free_all(fs, &d);
	return (0);
}
