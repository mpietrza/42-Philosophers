/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:08:14 by mpietrza          #+#    #+#             */
/*   Updated: 2024/10/04 15:40:58 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "philo.h"

void	ft_free_philos(t_philo **ps)
{
	int	i;

	i = 0;
	if (ps)
	{
		while (i < ps[i]->nbr_of_philos - 1)
		{
			if (ps[i]->philo)
				ps[i]->philo = 0;
			if (ps[i]->fork_l)
				pthread_mutex_destroy(ps[i]->fork_l);
			if (ps[i]->fork_r)
				pthread_mutex_destroy(ps[i]->fork_r);
			if (ps[i]->write_lock)
				pthread_mutex_destroy(ps[i]->write_lock);
			if (ps[i]->death_lock)
				pthread_mutex_destroy(ps[i]->death_lock);
			if (ps[i]->meal_lock)
				pthread_mutex_destroy(ps[i]->meal_lock);
			if (ps[i]->meal_lock)
				pthread_mutex_destroy(ps[i]->meal_lock);
			if (ps[i])
				free(ps[i]);
			i++;
		}
		if (ps[i])
		{
			free(ps[i]);
			ps[i] = NULL;
		}
		free(ps);
		ps = NULL;
	}

}

void	ft_free_forks(t_mtx *fs, int nbr_of_philos)
{
	int	i;

	i = 0;
	if (fs)
	{
		while (i < nbr_of_philos - 1)
		{
			pthread_mutex_destroy(&fs[i]);
			i++;
		}
		free(fs);
	}
}

void	ft_free_data(t_data *d)
{
	if (d)
	{
		pthread_mutex_destroy(&d->death_lock);
		pthread_mutex_destroy(&d->meal_lock);
		pthread_mutex_destroy(&d->write_lock);
		if (d->ps)
			ft_free_philos(d->ps);
		free(d);
	}
}

int	ft_err_exit(t_data *d, t_mtx *fs, const char *err_message, int ret)
{
	printf("Error!\n%s\n", err_message);
	if (d)
		ft_free_data(d);
	if (fs)
		ft_free_forks(fs, d->nbr_of_philos);
	return (ret);
}

