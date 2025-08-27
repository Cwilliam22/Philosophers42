/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:08:50 by wcapt             #+#    #+#             */
/*   Updated: 2025/08/26 14:50:09 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

t_infos	*init_infos(char **argv)
{
	t_infos *infos;
	
	infos->nb_philo = ft_atol(argv[1]);
	infos->time_to_die = ft_atol(argv[2]);
	infos->time_to_eat = ft_atol(argv[3]);
	infos->time_to_sleep = ft_atol(argv[4]);
	if (argv[5] != NULL)
		infos->number_of_meals = ft_atol(argv[5]);
	else
		infos->number_of_meals = -1;
	return (infos);
}

t_philo	*init_philo_struct(char **argv, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philo[i].id = i;
		philo[i].meals = 0;
		philo[i].last_meal = 0;
		philo[i].left = 0;
		philo[i].right = 0;
		i++;
	}
	return (philo);
}

/*
(1)
	structure_name.member1;
	structure_name.member2;
(2)
	structure_ptr->member1
	structure_ptr->member2
*/
