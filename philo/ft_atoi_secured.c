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

static int	ft_skip_blanks_and_sign(const char *str, int pos_neg)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
		pos_neg = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	return (i);
}

int	ft_atoi_secured(const char *str, t_data *d)
{
	int		i;
	long	result;
	int		pos_neg;

	result = 0;
	pos_neg = 1;
	i = ft_skip_blanks_and_sign(str, pos_neg);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	if ((result > INT_MAX && pos_neg == 1)
		|| (result - 1 > INT_MAX && pos_neg == -1))
	{
		result = INT_MAX;
		d->is_atoi_error == true;
	}
	return ((int)pos_neg * result);
}
