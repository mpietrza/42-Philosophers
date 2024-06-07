/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:08:51 by mpietrza          #+#    #+#             */
/*   Updated: 2024/06/07 16:08:55 by mpietrza         ###   ########.fr       */
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

static void	ft_check_argv_err_message(int i)
{
	printf("Error!\n");
	if (i == 1)
		printf("Invalid number of philosophers\n");
	else if (i == 2)
		printf("Invalid time to die\n");
	else if (i == 3)
		printf("Invalid time to eat\n");
	else if (i == 4)
		printf("Invalid time to sleep\n");
	else if (i == 5)
	{
		printf("Invalid number of times each philosopher");
		printf(" must eat");
	}
}

bool	ft_check_argv(const char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		while (argv[i][j])
		{	
			if (ft_my_isdigit(s[i][j]) == false)
			{
				ft_check_argv_err_message(i);
				return (false);
			}
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
