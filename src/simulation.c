/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:15:26 by wcapt             #+#    #+#             */
/*   Updated: 2025/09/06 16:50:14 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int      all_finish(t_infos *infos)
{
        int                     i;

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
	print_action(philo->infos, "has taken a fork", philo->id);
	ft_usleep(philo->infos->time_to_die);
	print_action(philo->infos, "died", philo->id);
	pthread_mutex_unlock(&philo->left_fork->mtx);
	pthread_mutex_lock(&philo->infos->dead_mutex);
	philo->infos->simulation_stop = 1;
	pthread_mutex_unlock(&philo->infos->dead_mutex);
}

void	*monitor(void *data)
{
	t_infos		*infos;
	int			i;
	int			stop;
	long long	last_meal;
	int			finish;

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
			if (all_finish(infos))
				break ;
			pthread_mutex_lock(&infos->philos[i].meal_mutex);
			last_meal = infos->philos[i].last_meal;
			finish = infos->philos[i].finish_meals;
			pthread_mutex_unlock(&infos->philos[i].meal_mutex);
			if ((time_is_flying_ms() - last_meal
				> infos->time_to_die) && !finish)
			{
				print_action(infos, "died", infos->philos[i].id);
				pthread_mutex_lock(&infos->dead_mutex);
				infos->simulation_stop = 1;
				pthread_mutex_unlock(&infos->dead_mutex);
				break ;
			}
			i++;
		}
		ft_usleep(1);
	}
	return (NULL);
}

void	*philo_rout(void *data)
{
	t_philos	*philo;
	int			stop;

	philo = (t_philos *)data;
	while (time_is_flying_ms() < philo->infos->start)
		usleep(100);
	if (philo->infos->nb_philo == 1)
		return (one_philo(philo), NULL);
	while (1)
	{
		pthread_mutex_lock(&philo->infos->dead_mutex);
		stop = philo->infos->simulation_stop;
		pthread_mutex_unlock(&philo->infos->dead_mutex);
		if (stop)
			break ;
		if (philo->meals_eaten >= philo->infos->number_of_meals
			&& philo->infos->number_of_meals > 0)
		{
			pthread_mutex_lock(&philo->meal_mutex);
			philo->finish_meals = 1;
			pthread_mutex_unlock(&philo->meal_mutex);
			break ;
		}
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
