/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:15:26 by wcapt             #+#    #+#             */
/*   Updated: 2025/09/01 20:31:43 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*philo_rout(void *data)
{
	t_philos	*philos;

	philos = (t_philos *)data;
	if (philos->infos->number_of_meals == 0)
		return (NULL);
	else
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

