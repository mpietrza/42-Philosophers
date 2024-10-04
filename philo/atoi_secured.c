/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_secured.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:02:07 by mpietrza          #+#    #+#             */
/*   Updated: 2024/06/12 19:04:11 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_skip_blanks_and_sign(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		return (-1);
	else if (str[i] == '+')
		i++;
	return (i);
}

size_t	ft_atos_t_positive(const char *str)
{
	int	i;
	size_t	result;

	result = 0;
	i = ft_skip_blanks_and_sign(str);
	if (i == -1)
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	if (result > SIZE_MAX)
		return (-1);
	return (result);
}
