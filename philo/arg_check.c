/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:08:51 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/01 17:40:36 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int     ft_my_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (TRUE);
	if (c == '+')
		return (TRUE);
	if (c == ' ' || c == 9)
		return (TRUE);
	return (FALSE);
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

int	ft_check_argv(const char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{	
			if (ft_my_isdigit(argv[i][j]) == FALSE)
			{
				ft_check_argv_err_message(i);
				return (FALSE);
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}


/*
char	*ft_strchr(const char *s, int c)
{
	int	i;

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
