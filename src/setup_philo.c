/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:11:41 by wcapt             #+#    #+#             */
/*   Updated: 2025/08/29 13:13:21 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/*
pthread_mutex_t	*create_forks(int N)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * N);
	if (!forks)
		return (NULL);
	while (i < N)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}
*/
