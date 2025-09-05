/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt <wcapt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:15:26 by wcapt             #+#    #+#             */
/*   Updated: 2025/09/05 18:05:12 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*monitor(void *data)
{
	t_philos	*philo;
	t_infos		*infos;
	int			i;

	philo = (t_philos *)data;
	infos = philo->infos;
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
		usleep(1000);
	}
	return (NULL);
}

void	*philo_rout(void *data)
{
	t_philos	*philo;
	t_infos		*infos;

	philo = (t_philos *)data;
	infos = philo->infos;
	while (!infos->simulation_stop)
	{
		if (philo->meals_eaten >= infos->number_of_meals &&
			infos->number_of_meals > 0)
			break ;
		if (infos->philos->id % 2 == 0)
			take_a_fork(infos, 'l');
		else if (infos->philos->id % 2 != 0)
			take_a_fork(infos, 'r');
		if (philo->r_fork)
			take_a_fork(infos, 'l');
		if (philo->r_fork && philo->l_fork)
		{
			print_action(infos, "is eating", philo->id);
			ft_usleep(infos->time_to_eat);
			philo->meals_eaten++;
			philo->last_meal = time_is_flying_ms() - infos->start;
			release_forks_and_sleep(philo);
		}
	}
	return (NULL);
}

int	start_simulation(t_infos *infos)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	infos->start = time_is_flying_ms();
	if (infos->philos->id % 2 != 0)
		ft_usleep(infos->time_to_eat);
	while (i < infos->nb_philo)
	{
		if (pthread_create(&infos->philos[i].thread, NULL, &philo_rout,
				&infos->philos[i]) != 0)
		{
			print_error(RED "Fail to creat thread for the pilosophers" RESET
				"\n", -1, NULL, 2);
			return (0);
		}
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, &monitor, infos) != 0)
	{
		print_error(RED "Fail to creat thread for the monitor" RESET
			"\n", -1, NULL, 2);
		return (0);
	}
	return (1);
}
