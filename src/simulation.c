/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt <wcapt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:15:26 by wcapt             #+#    #+#             */
/*   Updated: 2025/09/02 17:04:19 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*philo_rout(void *data)
{
	t_philos	*philos;

	philos = (t_philos *)data;
	//mettre à jour last_meal_ms
	//afficher “is eating”,
	//dormir time_to_eat,
	//incrémenter meals_eaten,
	//reposer les 2 fourchettes.
	//Dormir (time_to_sleep) “is sleeping”.
	//Penser “is thinking”, petite micro-pause pour desserrer la contention.
	//Si number_of_meals est défini et atteint → sortir de la boucle.
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
