/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:01:35 by mpietrza          #+#    #+#             */
/*   Updated: 2024/05/28 19:40:44 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool     ft_my_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	if (c == '+')
		return (true);
	if (c == ' ' || c == 9)
		return (true);
	return (false);
}

bool	ft_check_argv(const char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		while (argv[i][j])
		{	
			if (ft_my_isdigit(s[i][j]) == false)
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

/*
char	*ft_strchr(const char *s, int c)
{
	long	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}*/
