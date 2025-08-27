/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:45:13 by wcapt             #+#    #+#             */
/*   Updated: 2025/08/26 14:42:06 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

#include <limits.h>

# include "../libft/includes/libft.h"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

#define NB_MAX_PHILO 200

typedef struct s_infos
{
	long int	nb_philo;
	long int	time_to_die;
	long int	time_to_eat;
	long int	time_to_sleep;
	long int	number_of_meals;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	int				simulation_stop;
}	t_infos;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				meals;
	long			last_meal;
	int				left;
	int				right;
	t_infos			*data;
}	t_philo;


// main.c

// parse.c
int		parse(char **argv);

// init.c
int		init_infos(char **argv);

// utils.c
void	print_error_parse(char *begin, char *end, int i);


#endif