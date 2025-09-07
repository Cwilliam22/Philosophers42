
#include "../include/philosophers.h"

void	*monitor(void *data)
{
	t_infos		*infos;
	int			i;
	int			stop;
	long long	last_meal;
	int			finish;

	infos = (t_infos *)data;
	while (1)
	{
		i = 0;
		pthread_mutex_lock(&infos->dead_mutex);
		stop = infos->simulation_stop;
		pthread_mutex_unlock(&infos->dead_mutex);
		if (stop)
			break ;
		while (i < infos->nb_philo)
		{
			if (all_finish(infos))
				break ;
			pthread_mutex_lock(&infos->philos[i].meal_mutex);
			last_meal = infos->philos[i].last_meal;
			finish = infos->philos[i].finish_meals;
			pthread_mutex_unlock(&infos->philos[i].meal_mutex);
			if ((time_is_flying_ms() - last_meal
					> infos->time_to_die) && !finish)
			{
				print_action(infos, "died", infos->philos[i].id);
				pthread_mutex_lock(&infos->dead_mutex);
				infos->simulation_stop = 1;
				pthread_mutex_unlock(&infos->dead_mutex);
				break ;
			}
			i++;
		}
		ft_usleep(1);
	}
	return (NULL);
}
