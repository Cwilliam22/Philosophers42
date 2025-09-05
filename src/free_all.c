/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt <wcapt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:11:58 by wcapt             #+#    #+#             */
/*   Updated: 2025/09/05 17:53:49 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	wait_before_destroy(t_infos *infos)
{
	int	i;

	i = 0;
	while (i < infos->nb_philo)
	{
		if (pthread_join(infos->philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	clean_all(t_infos *infos)
{
	destroy_mutex(infos);
	if (!infos)
		return (0);
	if (!wait_before_destroy(infos))
		return (0);
	destroy_mutex(infos);
	pthread_mutex_destroy(&infos->print_mutex);
	if (infos->forks)
		free(infos->forks);
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
}
