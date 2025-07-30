/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt <wcapt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:45:13 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/30 01:18:44 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# include "../libft/includes/libft.h"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

typedef struct s_infos
{
	long int	number_of_philosophers;
	long int	time_to_die;
	long int	time_to_eat;
	long int	time_to_sleep;
	long int	number_of_meals;

	t_philo			*philos;	// Tableau de philosophes
	pthread_mutex_t	*forks;	// Tableau de mutex (fourchettes)
	pthread_mutex_t	print_mutex;	// Mutex pour les printf synchronisés
	int				simulation_stop;	// Flag pour arrêter proprement (ex : si un philosophe meurt)
}	t_infos;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long int		last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_infos	*infos;
}	t_philo;


// main.c

// parse.c
int	valid_unsigned_integer(char **argv);
int	parse(char **argv);

// init.c
int	init_all(t_infos *infos, char **argv);

#endif