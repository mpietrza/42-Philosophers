/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milosz <milosz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:31:12 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/10 22:21:38 by milosz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_print_data(t_data *d)
{
	printf("d->nbr_of_philos = %d\n", d->nbr_of_philos);
	printf("d->write_lock = %p\n", (void *)&(d->write_lock));
	printf("d->meal_lock = %p\n", (void *)&(d->meal_lock));
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strjoin_space(const char *s1, const char *s2)
{
	char	*s3;
	size_t	len1;
	size_t	len2;
	size_t	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s3 = (char *)malloc((len1 + 1 + len2 + 1) * sizeof(char));
	if (s3 == NULL)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		s3[i] = s1[i];
		i++;
	}
	s3[i] = ' ';
	i++;
	while (i < len1 + len2 + 1)
	{
		s3[i] = s2[i - len1 - 1];
		i++;
	}
	s3[i] = '\0';
	return (s3);
}

char *ft_join_3_str(char *s1, char *s2, char *s3)
{
	char *s12;
	char *s123;

	s123 = NULL;
	s12 = ft_strjoin_space(s1, s2);
	if (s12 == NULL)
		return (NULL);
	s123 = ft_strjoin_space(s12, s3);
	free(s12);
	if (s123 == NULL)
		return (NULL);
	return (s123);
}
