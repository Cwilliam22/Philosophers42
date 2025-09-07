/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 19:44:33 by wcapt             #+#    #+#             */
/*   Updated: 2025/09/07 20:07:56 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	monitor_check(t_infos *infos, int *i)
{
	long long	last_meal;
	int			finish;

	if (all_finish(infos))
		return (0);
	pthread_mutex_lock(&infos->philos[*i].meal_mutex);
	last_meal = infos->philos[*i].last_meal;
	finish = infos->philos[*i].finish_meals;
	pthread_mutex_unlock(&infos->philos[*i].meal_mutex);
	if ((time_is_flying_ms() - last_meal
			> infos->time_to_die) && !finish)
	{
		print_action(infos, "died", infos->philos[*i].id);
		pthread_mutex_lock(&infos->dead_mutex);
		infos->simulation_stop = 1;
		pthread_mutex_unlock(&infos->dead_mutex);
		return (0);
	}
	return (1);
}

void	*monitor(void *data)
{
	t_infos		*infos;
	int			i;
	int			stop;

	infos = (t_infos *)data;
	while (1)
	{
		i = 0;
		pthread_mutex_lock(&infos->dead_mutex);
		stop = infos->simulation_stop;
		pthread_mutex_unlock(&infos->dead_mutex);
		if (stop)
			break ;
		while (i < infos->nb_philo)
		{
			if (!monitor_check(infos, &i))
				break ;
			i++;
		}
		ft_usleep(1);
	}
	return (NULL);
}
