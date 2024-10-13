/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:08:51 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/13 16:23:46 by mpietrza         ###   ########.fr       */
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

static int ft_check_argv_err_message(int i)
{
	printf("Error!\n");
	if (i == 0)
		printf("Invalid number of arguments\n");
	else if (i == 1)
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
		printf(" must eat\n");
	}
	return (FALSE);
}

static int ft_check_argv(const char **argv)
{
	int	i;
	int	j;
	int flag;

	i = 1;
	flag = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{	
			if (ft_my_isdigit(argv[i][j]) == FALSE)
			{
				flag += 1;
				ft_check_argv_err_message(i);
				break;
			}
			j++;
		}
		i++;
	}
	if (flag)
		return (FALSE);
	return (TRUE);
}

int	ft_check_arg(int argc, const char **argv)
{
	if (!argv)
		return (FALSE);
	if (!(argc == 5 || argc == 6))
		return (ft_check_argv_err_message(0));
	if (argv[1][0] == '0')
		return (ft_check_argv_err_message(1));
	if (ft_check_argv(argv) == FALSE)
		return (FALSE);
	return (TRUE);
}

