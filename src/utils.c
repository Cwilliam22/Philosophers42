/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt <wcapt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:12:18 by wcapt             #+#    #+#             */
/*   Updated: 2025/09/05 17:54:28 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long long	time_is_flying_ms(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return (timeval.tv_sec * 1000 + timeval.tv_usec / 1000);
}

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
	
	time = 0;
	time = time_is_flying_ms() - infos->start;
	pthread_mutex_lock(&infos->print_mutex);
	if (!infos->simulation_stop)
		printf("[" GREEN "%lld" RESET "] Philo %d %s\n", time, id, todo);
	pthread_mutex_unlock(&infos->print_mutex);
}

void	ft_usleep(long long time)
{
	long long start;

	start = time_is_flying_ms();
	while(time_is_flying_ms() - start < time)
		usleep(100);
}

void	take_a_fork(t_infos *infos, char the_fork)
{
	int		*taken;
	t_forks	*forks;
	
	while (!infos->simulation_stop)
	{
		taken = &(infos->philos->l_fork);
		forks = infos->philos->left_fork;
		if (the_fork == 'r')
		{
			taken = &(infos->philos->l_fork);
			forks = infos->philos->left_fork;
		}
		pthread_mutex_lock(&forks->mtx);
		if (!(*taken) && !forks->used)
		{
			*taken = 1;
			forks->used = 1;
			pthread_mutex_unlock(&(forks->mtx));
			print_action(infos, "has taken a fork", infos->philos->id);
		}
		else
			pthread_mutex_unlock(&(forks->mtx));
	}
}
	

void	release_fork(char fork_name, t_philos *philos)
{
	int		*taken;
	t_forks	*forks;

	taken = &(philos->r_fork);
	forks = philos->right_fork;
	if (fork_name == 'l')
	{
		taken = &(philos->l_fork);
		forks = philos->left_fork;
	}
	pthread_mutex_lock(&(forks->mtx));
	*taken = 0;
	forks->used = 0;
	pthread_mutex_unlock(&(forks->mtx));
}

void	release_forks_and_sleep(t_philos *philo)
{
	release_fork('r', philo);
	release_fork('l', philo);
	print_action(philo->infos, "is sleeping", philo->id);
	ft_usleep(philo->infos->time_to_sleep);
	print_action(philo->infos, "is thinking", philo->id);
}