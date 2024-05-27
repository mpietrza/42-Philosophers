/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_secured.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:02:07 by mpietrza          #+#    #+#             */
/*   Updated: 2024/05/14 14:02:12 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

static int	ft_skip_blanks_and_sign(const char *str, t_data *d)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
		d->atoi_error_index = -1;
		return (-1);
	}
	else if (str[i] == '+')
		i++;
	return (i);
}

unsigned int	ft_atoui_secured(const char *str, t_data *d)
{
	int		i;
	long	result;

	result = 0;
	i = ft_skip_blanks_and_sign(str, d);
	if (i == -1)
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	if (result > INT_MAX)
	{
		result = INT_MAX + 1;
		d->atoi_error_index = 1;
	}
	return (result);
}
