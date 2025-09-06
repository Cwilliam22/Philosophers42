/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:12:18 by wcapt             #+#    #+#             */
/*   Updated: 2025/09/06 16:41:51 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static	char	*join_and_free(char *str1, char *str2)
{
	char	*result;

	if (!str1 || !str2)
	{
		free(str1);
		free(str2);
		return (NULL);
	}
	result = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (result);
}

void	print_error(char *begin, int i, char *end, int out)
{
	char	*idx;
	char	*start;
	char	*finish;

	start = ft_strdup(begin);
	if (end)
		finish = ft_strdup(end);
	if (i != -1)
	{
		idx = ft_itoa(i);
		start = join_and_free(start, idx);
	}
	if (end)
		start = join_and_free(start, finish);
	write(out, start, ft_strlen(start));
	free(start);
}

void	print_action(t_infos *infos, char *todo, int id)
{
	long long	time;
	int			stop;

	time = time_is_flying_ms() - infos->start;
	pthread_mutex_lock(&infos->print_mutex);
	pthread_mutex_lock(&infos->dead_mutex);
	stop = infos->simulation_stop;
	pthread_mutex_unlock(&infos->dead_mutex);
	if (!stop || (todo && !ft_strcmp(todo, "died")))
		printf(NAVY "%lld [ms] " RESET "Philo " BLUE "%d " RESET
			"%s\n", time, id + 1, todo);
	pthread_mutex_unlock(&infos->print_mutex);
}
