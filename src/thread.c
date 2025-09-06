
#include "../include/philosophers.h"

int	join_threads(t_infos *infos)
{
	int	i;

	i = 0;
	while (i < infos->nb_philo)
	{
		if (pthread_join(infos->philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	pthread_join(infos->monitor_thread, NULL);
	return (1);
}

int	create_threads(t_infos *infos)
{
	int	i;

	i = 0;
	while (i < infos->nb_philo)
	{
		infos->philos[i].last_meal = infos->start;
		if (pthread_create(&infos->philos[i].thread, NULL, &philo_rout,
				&infos->philos[i]) != 0)
		{
			cleanup_threads(infos, i);
			print_error(RED "Fail to creat thread for the pilosophers" RESET
				"\n", -1, NULL, 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	cleanup_threads(t_infos *infos, int num_thread)
{
	int	i;
	int	j;

	infos->simulation_stop = 1;
	i = 0;
	while (i < num_thread)
	{
		j = pthread_join(infos->philos[i].thread, NULL);
		if (j != 0)
			return (0);
		i++;
	}
	return (1);
}
