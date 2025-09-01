/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:12:11 by wcapt             #+#    #+#             */
/*   Updated: 2025/09/01 14:58:33 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_arg_struct_infos(t_infos *infos)
{
	printf("nb_arg : %d\n", infos->nb_arg);
	printf("nb_philo : %d\n", infos->nb_philo);
	printf("time_to_die : %lld\n", infos->time_to_die);
	printf("time_to_eat : %lld\n", infos->time_to_eat);
	printf("time_to_sleep : %lld\n", infos->time_to_sleep);
}
