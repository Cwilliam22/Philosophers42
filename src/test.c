/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:12:11 by wcapt             #+#    #+#             */
/*   Updated: 2025/08/29 13:12:46 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_arg_struct_infos(t_infos *infos)
{
	printf("nb_arg : %zu\n", infos->nb_arg);
	printf("nb_philo : %ld\n", infos->nb_philo);
	printf("time_to_die : %ld\n", infos->time_to_die);
	printf("time_to_eat : %ld\n", infos->time_to_eat);
	printf("time_to_sleep : %ld\n", infos->time_to_sleep);
}
