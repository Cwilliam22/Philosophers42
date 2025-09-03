/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:15:26 by wcapt             #+#    #+#             */
/*   Updated: 2025/09/03 23:47:46 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*philo_rout(void *data)
{
	t_philos	*philo;
	t_infos		*infos;

	philo = (t_philos *)data;
	infos = philo->infos;
	while (!infos->simulation_stop)
	{
		// Prendre les fourchettes (toujours dans le même ordre pour éviter deadlock)
		pthread_mutex_lock(&philo->left_fork->mtx);
		pthread_mutex_lock(&philo->right_fork->mtx);
		philo->last_meal = time_is_flying_ms();
		print_action(infos, "is eating");
		usleep(infos->time_to_eat * 1000);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->left_fork->mtx);
		pthread_mutex_unlock(&philo->right_fork->mtx);
		print_action(infos, "is sleeping");
		usleep(infos->time_to_sleep * 1000);
		print_action(infos, "is thinking");
		usleep(100); // micro-pause pour éviter la contention
		if (infos->number_of_meals > 0 && philo->meals_eaten >= infos->number_of_meals)
			break;
	}
	return (NULL);
}

int	start_simulation(t_infos *infos)
{
	int	i;

	i = 0;
	infos->start = time_is_flying_ms() + (infos->nb_philo * MORE_TIME);
	while (i < infos->nb_philo)
	{
		if (pthread_create(&infos->philos[i].thread, NULL, &philo_rout, &infos->philos[i]) != 0)
		{
			print_error(RED "Fail to creat thread for the pilosophers" RESET
					"\n", -1, NULL, 2);
			return (0);
		}
		i++;
	}
	return (1);
}


// start_simulation()
// boucle infini tant qu'aucun philo ne meurt
// lancer un monitor qui surveille les philos (pret a detecter la mort d'un philo)
// chaque philo tourne dans une boucle 


//Le mutex de print empêche de mélanger une ligne en deux, mais n’impose pas un ordre global croissant des timestamps.
