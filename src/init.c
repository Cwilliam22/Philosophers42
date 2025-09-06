/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:08:50 by wcapt             #+#    #+#             */
/*   Updated: 2025/09/06 15:30:46 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

t_infos	*init_infos(char **argv)
{
	t_infos	*infos;

	infos = malloc(sizeof(*infos));
	if (!infos)
		return (NULL);
	infos->nb_arg = ft_arraylen(argv);
	infos->nb_philo = ft_atol(argv[1]);
	infos->time_to_die = ft_atol(argv[2]);
	infos->time_to_eat = ft_atol(argv[3]);
	infos->time_to_sleep = ft_atol(argv[4]);
	infos->simulation_stop = 0;
	if (argv[5] != NULL)
		infos->number_of_meals = ft_atol(argv[5]);
	else
		infos->number_of_meals = -1;
	if (pthread_mutex_init(&infos->print_mutex, NULL) != 0)
		return (free(infos), NULL);
	if (pthread_mutex_init(&infos->dead_mutex, NULL) != 0)
		return (free(infos), NULL);
	if (!init_forks(infos))
		return (free(infos), NULL);
	if (!init_philos(infos))
		return (free(infos->forks), free(infos), NULL);
	return (infos);
}

int	init_forks(t_infos *infos)
{
	int	i;

	i = 0;
	infos->forks = malloc(sizeof(t_forks) * infos->nb_philo);
	if (!infos->forks)
		return (0);
	while (i < infos->nb_philo)
	{
		if (pthread_mutex_init(&infos->forks[i].mtx, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&infos->forks[i].mtx);
			free(infos->forks);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_philos(t_infos *infos)
{
	int			i;
	t_philos	*philo;

	i = 0;
	infos->philos = malloc(sizeof(t_philos) * infos->nb_philo);
	if (!infos->nb_philo)
		return (0);
	while (i < infos->nb_philo)
	{
		philo = &infos->philos[i];
		philo->id = i;
		philo->infos = infos;
		philo->left_fork = &infos->forks[i];
		philo->right_fork = &infos->forks[(i + 1) % infos->nb_philo];
		philo->meals_eaten = 0;
		philo->finish_meals = 0;
		philo->last_meal = 0;
		if (pthread_mutex_init(&philo->meal_mutex, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&infos->philos[i].meal_mutex);
			free(infos->philos);
			return (0);
		}
		i++;
	}
	return (1);
}
