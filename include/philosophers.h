/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:45:13 by wcapt             #+#    #+#             */
/*   Updated: 2025/09/04 14:41:49 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# include <limits.h>

# include "../libft/includes/libft.h"

# define RED	"\033[31m"
# define GREEN "\033[32m"
# define RESET "\033[0m"

# define NB_MAX_PHILO 200

# define MORE_TIME 30

typedef struct s_forks
{
	pthread_mutex_t mtx;
}	t_forks;

typedef struct s_philos
{
	int				id;
	long long		last_meal;
	int				meals_eaten;
	pthread_t		thread;
	t_forks			*left_fork;
	t_forks			*right_fork;
	struct s_infos	*infos;
}	t_philos;

typedef struct s_infos
{
	int				nb_arg;
	int				nb_philo;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				number_of_meals;
	long long		start;
	t_philos		*philos;
	t_forks			*forks;
	pthread_mutex_t	print_mutex;
	int				simulation_stop;
}	t_infos;

// main.c

// parse.c
int			parse(char **argv);

// init.c
t_infos		*init_infos(char **argv);
int			init_forks(t_infos *infos);
int			init_philos(t_infos *infos);

// utils.c
void		print_error(char *begin, int i, char *end, int out);
long long	time_is_flying_ms(void);
void		print_action(t_infos *infos, char *todo, int id);

// simulation.c
int			start_simulation(t_infos *infos);
void		*philo_rout(void *data);

// free_all.c
void		clean_all(t_infos *infos);
void		destroy_mutex(t_infos *infos);

//test.c
void		print_arg_struct_infos(t_infos *infos);

#endif