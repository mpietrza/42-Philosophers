/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:10:57 by mpietrza          #+#    #+#             */
/*   Updated: 2024/05/13 15:21:41 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
//	t_timeval

	return (milisecs);
}

int	main(int argc, char **argv)
{
	t_data	*d;

	if (!(argc == 5 || argc == 6) || ft_check_argv(argv) == false)
		return (1);
	d = ft_prase_input(argc, argv);
	if (!d)
		return (1);

	return (0);
}
