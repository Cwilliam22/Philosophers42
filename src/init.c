/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:08:50 by wcapt             #+#    #+#             */
/*   Updated: 2025/08/29 13:13:53 by wcapt            ###   ########.fr       */
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
	if (argv[5] != NULL)
		infos->number_of_meals = ft_atol(argv[5]);
	else
		infos->number_of_meals = -1;
	//if (!init_forks())
	//	return (NULL);
	//if (!init_philos())
	//	return (NULL);
	return (infos);
}

/*
t_philo	*init_philo_struct(char **argv, t_philo *philo)
{
	philo = malloc(sizeof(*infos));
	if (!philo)
		return (NULL);
	return (philo);
}
*/

/*
(1)
	structure_name.member1;
	structure_name.member2;
(2)
	structure_ptr->member1
	structure_ptr->member2
*/
