/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt <wcapt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:15:26 by wcapt             #+#    #+#             */
/*   Updated: 2025/09/07 10:01:20 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	all_finish(t_infos *infos)
{
	int	i;

	i = 0;
	while (i < infos->nb_philo)
	{
		pthread_mutex_lock(&infos->philos[i].meal_mutex);
		if (infos->philos[i].finish_meals == 0)
		{
			pthread_mutex_unlock(&infos->philos[i].meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&infos->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_lock(&infos->dead_mutex);
	infos->simulation_stop = 1;
	pthread_mutex_unlock(&infos->dead_mutex);
	return (1);
}

static void	one_philo(t_philos *philo)
{
	pthread_mutex_lock(&philo->left_fork->mtx);
	philo->left_fork->is_taken = 1;
	print_action(philo->infos, "has taken a fork", philo->id);
	ft_usleep(philo->infos->time_to_die);
	print_action(philo->infos, "died", philo->id);
	philo->left_fork->is_taken = 0;
	pthread_mutex_unlock(&philo->left_fork->mtx);
	pthread_mutex_lock(&philo->infos->dead_mutex);
	philo->infos->simulation_stop = 1;
	pthread_mutex_unlock(&philo->infos->dead_mutex);
}

int	look_at_meal(t_philos *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	if (philo->meals_eaten >= philo->infos->number_of_meals
		&& philo->infos->number_of_meals > 0)
	{
		philo->finish_meals = 1;
		pthread_mutex_unlock(&philo->meal_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (1);
}

int	routine(t_philos *philo)
{
	int	stop;
	int	forks;

	pthread_mutex_lock(&philo->infos->dead_mutex);
	stop = philo->infos->simulation_stop;
	pthread_mutex_unlock(&philo->infos->dead_mutex);
	if (stop)
		return (0) ;
	if (!look_at_meal(philo))
		return (0) ;
	if (philo->id % 2 == 0)
		forks = take_a_fork(philo, 'l');
	else
		forks = take_a_fork(philo, 'r');
	if (forks)
	{
		eat_this(philo);
		sleep_and_think(philo);
	}
	return (1);
}

void	*philo_routine(void *data)
{
	t_philos	*philo;

	philo = (t_philos *)data;
    while (time_is_flying_ms() < philo->infos->start)
        ft_usleep(10);
    if (philo->id % 2 != 0)
        ft_usleep(philo->infos->time_to_eat / 2);
    if (philo->infos->nb_philo == 1)
        return (one_philo(philo), NULL);
    while (1)
	{
		if (!routine(philo))
			break;
	}
	return (NULL);
}

int	start_simulation(t_infos *infos)
{
	infos->start = time_is_flying_ms() + 100;
	if (!create_threads(infos))
		return (0);
	if (pthread_create(&infos->monitor_thread, NULL, &monitor, infos) != 0)
	{
		cleanup_threads(infos, infos->nb_arg);
		print_error(RED "Fail to creat thread for the monitor" RESET
			"\n", -1, NULL, 2);
		return (0);
	}
	return (1);
}
