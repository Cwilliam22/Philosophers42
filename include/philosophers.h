/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt <wcapt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:45:13 by wcapt             #+#    #+#             */
/*   Updated: 2025/08/28 14:46:37 by wcapt            ###   ########.fr       */
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
	size_t		nb_arg;
	long int	nb_philo;
	long int	time_to_die;
	long int	time_to_eat;
	long int	time_to_sleep;
	long int	number_of_meals;
	//t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	int				simulation_stop;
}	t_infos;

typedef struct s_philo
{
	int               id;
	long int          last_meal_ms;
	long int          meals_eaten;
	pthread_t         thread;
	pthread_mutex_t  *left_fork;
	pthread_mutex_t  *right_fork;
	struct s_infos   *infos;
} t_philo;


// main.c

// parse.c
int		parse(char **argv);

// init.c
t_infos		*init_infos(char **argv);

// utils.c
void	print_error_parse(char *begin, int i, char *end);
//size_t	ft_arraylen(char **array);


#endif