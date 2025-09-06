/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:45:13 by wcapt             #+#    #+#             */
/*   Updated: 2025/09/06 17:21:05 by wcapt            ###   ########.fr       */
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
# define GREEN	"\033[32m"
# define BLUE	"\033[34m"
# define NAVY	"\033[38;5;19m"
# define RESET	"\033[0m"

# define NB_MAX_PHILO 200

# define MORE_TIME 30

typedef struct s_forks
{
	pthread_mutex_t	mtx;
}	t_forks;

typedef struct s_philos
{
	int				id;
	long long		last_meal;
	int				meals_eaten;
	pthread_t		thread;
	t_forks			*left_fork;
	t_forks			*right_fork;
	int				finish_meals;
	pthread_mutex_t	meal_mutex;
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
	pthread_mutex_t	dead_mutex;
	int				simulation_stop;
	pthread_t		monitor_thread;
}	t_infos;

// main.c

// action.c
void		take_a_fork(t_philos *philo, char the_fork);
void		eat_this(t_philos *philo);
void		sleep_and_think(t_philos *philo);

// free_all.c
int			clean_all(t_infos *infos);
void		destroy_mutex(t_infos *infos);

// init.c
t_infos		*init_infos(char **argv);
int			init_forks(t_infos *infos);
int			init_philos(t_infos *infos);

// parse.c
int			parse(char **argv);

// simulation.c
int			start_simulation(t_infos *infos);
void		*monitor(void *data);
void		*philo_rout(void *data);

// thread.c
int			join_threads(t_infos *infos);
int			create_threads(t_infos *infos);
int			cleanup_threads(t_infos *infos, int num_thread);

// time.c
void		ft_usleep(long long time);
long long	time_is_flying_ms(void);

// utils.c
void		print_error(char *begin, int i, char *end, int out);
void		print_action(t_infos *infos, char *todo, int id);

#endif