/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:07:46 by wcapt             #+#    #+#             */
/*   Updated: 2025/09/05 20:10:28 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	take_a_fork(t_philos *philo, char the_fork)
{
	if (the_fork == 'l')
	{
		pthread_mutex_lock(&philo->left_fork->mtx);
		print_action(philo->infos, "has taken a fork", philo->id);
		pthread_mutex_lock(&philo->right_fork->mtx);
		print_action(philo->infos, "has taken a fork", philo->id);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->mtx);
		print_action(philo->infos, "has taken a fork", philo->id);
		pthread_mutex_lock(&philo->left_fork->mtx);
		print_action(philo->infos, "has taken a fork", philo->id);
	}
}

void	eat_this(t_philos *philo)
{
	print_action(philo->infos, "is eating", philo->id);
	philo->last_meal = time_is_flying_ms();
	ft_usleep(philo->infos->time_to_eat);
	philo->meals_eaten++;
}

void	sleep_and_think(t_philos *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mtx);
	pthread_mutex_unlock(&philo->right_fork->mtx);
	print_action(philo->infos, "is sleeping", philo->id);
	ft_usleep(philo->infos->time_to_sleep);
	print_action(philo->infos, "is thinking", philo->id);
}
