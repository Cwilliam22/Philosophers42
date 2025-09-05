/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:15:26 by wcapt             #+#    #+#             */
/*   Updated: 2025/09/05 20:21:55 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	one_philo(t_philos *philo)
{
	pthread_mutex_lock(&philo->left_fork->mtx);
	print_action(philo->infos, "has taken a fork", philo->id);
	ft_usleep(philo->infos->time_to_die);
	print_action(philo->infos, "died", philo->id);
	pthread_mutex_unlock(&philo->left_fork->mtx);
	philo->infos->simulation_stop = 1;
}

void	*monitor(void *data)
{
	t_infos		*infos;
	int			i;

	infos = (t_infos *)data;
	while (!infos->simulation_stop)
	{
		i = 0;
		while (i < infos->nb_philo)
		{
			if ((time_is_flying_ms() - infos->philos[i].last_meal)
				> infos->time_to_die)
			{
				print_action(infos, "died", infos->philos[i].id);
				infos->simulation_stop = 1;
				break ;
			}
			i++;
		}
		ft_usleep(1000);
	}
	return (NULL);
}

static void	*philo_rout(void *data)
{
	t_philos	*philo;

	philo = (t_philos *)data;
	while (time_is_flying_ms() < philo->infos->start)
		ft_usleep(100);
	if (philo->infos->nb_philo == 1)
		return (one_philo(philo), NULL);
	while (!philo->infos->simulation_stop)
	{
		if (philo->meals_eaten >= philo->infos->number_of_meals
			&& philo->infos->number_of_meals > 0)
			break ;
		if (philo->id % 2 == 0)
			take_a_fork(philo, 'l');
		else
			take_a_fork(philo, 'r');
		eat_this(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}

int	start_simulation(t_infos *infos)
{
	int			i;

	i = 0;
	infos->start = time_is_flying_ms() + 100;
	while (i < infos->nb_philo)
	{
		infos->philos[i].last_meal = infos->start;
		if (pthread_create(&infos->philos[i].thread, NULL, &philo_rout,
				&infos->philos[i]) != 0)
		{
			print_error(RED "Fail to creat thread for the pilosophers" RESET
				"\n", -1, NULL, 2);
			return (0);
		}
		i++;
	}
	if (pthread_create(&infos->monitor_thread, NULL, &monitor, infos) != 0)
	{
		print_error(RED "Fail to creat thread for the monitor" RESET
			"\n", -1, NULL, 2);
		return (0);
	}
	return (1);
}
