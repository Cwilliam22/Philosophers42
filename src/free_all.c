/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:11:58 by wcapt             #+#    #+#             */
/*   Updated: 2025/09/06 17:29:23 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	clean_all(t_infos *infos)
{
	if (!infos)
		return (0);
	if (!join_threads(infos))
		return (0);
	destroy_mutex(infos);
	pthread_mutex_destroy(&infos->print_mutex);
	if (infos->philos)
	{
		free(infos->philos);
		infos->philos = NULL;
	}
	free(infos);
	return (1);
}

void	destroy_mutex(t_infos *infos)
{
	int	i;

	if (infos->forks)
	{
		i = 0;
		while (i < infos->nb_philo)
		{
			pthread_mutex_destroy(&infos->forks[i].mtx);
			i++;
		}
		free(infos->forks);
		infos->forks = NULL;
	}
	if (infos->philos)
	{
		i = 0;
		while (i < infos->nb_philo)
		{
			pthread_mutex_destroy(&infos->philos[i].meal_mutex);
			i++;
		}
	}
}
