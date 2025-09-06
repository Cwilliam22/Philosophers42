/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:07:46 by wcapt             #+#    #+#             */
/*   Updated: 2025/09/06 21:28:18 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	take_a_fork(t_philos *philo, char the_fork)
{
	int	stop;

	pthread_mutex_lock(&philo->infos->dead_mutex);
	stop = philo->infos->simulation_stop;
	pthread_mutex_unlock(&philo->infos->dead_mutex);
	if (stop)
		return (0);
	if (the_fork == 'l')
	{
		if (!take_left_fork(philo, stop))
			return (0);
	}
	else
	{
		if (!take_right_fork(philo, stop))
			return (0);
	}
	return (1);
}

int	take_right_fork(t_philos *philo, int stop)
{
	pthread_mutex_lock(&philo->right_fork->mtx);
	philo->right_fork->is_taken = 1;
	print_action(philo->infos, "has taken a fork", philo->id);
	pthread_mutex_lock(&philo->infos->dead_mutex);
	stop = philo->infos->simulation_stop;
	pthread_mutex_unlock(&philo->infos->dead_mutex);
	if (stop)
	{
		philo->right_fork->is_taken = 0;
		pthread_mutex_unlock(&philo->right_fork->mtx);
		return (0);
	}
	pthread_mutex_lock(&philo->left_fork->mtx);
	philo->left_fork->is_taken = 1;
	print_action(philo->infos, "has taken a fork", philo->id);
	return (1);
}

int	take_left_fork(t_philos *philo, int stop)
{
	pthread_mutex_lock(&philo->left_fork->mtx);
	philo->left_fork->is_taken = 1;
	print_action(philo->infos, "has taken a fork", philo->id);
	pthread_mutex_lock(&philo->infos->dead_mutex);
	stop = philo->infos->simulation_stop;
	pthread_mutex_unlock(&philo->infos->dead_mutex);
	if (stop)
	{
		philo->left_fork->is_taken = 0;
		pthread_mutex_unlock(&philo->left_fork->mtx);
		return (0);
	}
	pthread_mutex_lock(&philo->right_fork->mtx);
	philo->right_fork->is_taken = 1;
	print_action(philo->infos, "has taken a fork", philo->id);
	return (1);
}

void	eat_this(t_philos *philo)
{
	print_action(philo->infos, "is eating", philo->id);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = time_is_flying_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_usleep(philo->infos->time_to_eat);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
}

void	sleep_and_think(t_philos *philo)
{
	philo->left_fork->is_taken = 0;
	pthread_mutex_unlock(&philo->left_fork->mtx);
	philo->right_fork->is_taken = 0;
	pthread_mutex_unlock(&philo->right_fork->mtx);
	print_action(philo->infos, "is sleeping", philo->id);
	ft_usleep(philo->infos->time_to_sleep);
	print_action(philo->infos, "is thinking", philo->id);
	ft_usleep(MORE_TIME);
}
