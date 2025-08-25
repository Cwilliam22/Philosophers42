
#include "../include/philosophers.h"

// Create a new philosopher/node
static t_philo *philo_new(int id, pthread_mutex_t *left, pthread_mutex_t *right)
{
	t_philo *p;

	p = calloc(1, sizeof(*p));
	if (!p)
		return (NULL);
	p->id = id;
	p->meals_eaten = 0;
	p->last_meal = 0;
	p->left_fork  = left;
	p->right_fork = right;
	// p->next est déjà NULL grâce à calloc
	// revoir l'utiliter de calloc !!!
	return (p);
}

t_philo	*create_philosophers(int nb_ph, pthread_mutex_t *forks)
{
	int		i;
	t_philo *head;
	t_philo *curr;
	t_philo *node;

	i = 0;
	head = NULL;
	if (nb_ph <= 0 || !forks)
		return (NULL);
	while (i < nb_ph)
	{
		node = philo_new(i, &forks[i], &forks[(i + 1) % nb_ph]);
		if (!node)
		{
			t_philo *tmp = head;
			while (tmp)
			{
				t_philo *n = tmp->next;
				free(tmp);
				tmp = n;
			}
			return (NULL);
		}
		if (!head)
			head = node;
		else
		{
			curr = head;
			while (curr->next)
				curr = curr->next;
			curr->next = node;
		}
		i++;
	}
	return (head);
}

pthread_mutex_t	*create_forks_array(int N)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * N);
	if (!forks)
		return (NULL);
	while (i < N)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}
