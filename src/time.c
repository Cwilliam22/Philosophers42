/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt <wcapt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:12:40 by wcapt             #+#    #+#             */
/*   Updated: 2025/09/06 23:09:45 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long long	time_is_flying_ms(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return (timeval.tv_sec * 1000 + timeval.tv_usec / 1000);
}

void	ft_usleep(long long time)
{
	long long	start;

	start = time_is_flying_ms();
    while (time_is_flying_ms() - start + 5 < time)
        usleep(100);
    while (time_is_flying_ms() - start < time)
        usleep(10);
}
