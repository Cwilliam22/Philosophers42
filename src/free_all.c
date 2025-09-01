/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:11:58 by wcapt             #+#    #+#             */
/*   Updated: 2025/09/01 19:03:26 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	clean_all(t_infos *infos)
{
	destroy_mutex(infos);
	if (!infos)
		return ;
	// Need pthread_join() to avoid any problems with free and destroy_mutex() ???
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
