/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:10:57 by mpietrza          #+#    #+#             */
/*   Updated: 2024/06/05 17:10:46 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	d;
	t_philo	ps;
	t_mtx	fs;

	if (!(argc == 5 || argc == 6) || ft_check_argv(argv) == false)
		return (1);
	d = ft_prase_input(argc, argv);
	if (!d)
		return (write(2, "Memory allocation error\n", 25), 1);

	return (0);
}
