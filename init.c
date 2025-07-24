#include "philo.h"

// allocate memory & setup philosophers
int init_philosophers(int nb_philos, pthread_t **threads, t_philo **philos)
{
    *threads = malloc(sizeof(pthread_t) * nb_philos);
    *philos = malloc(sizeof(t_philo) * nb_philos);
    if (!(*threads) || !(*philos))
        return (1);
    return (0);
} 

int init_shared(t_shared **shared, char **argv, int argc)
{
    *shared = malloc(sizeof(t_shared));
	if(!*shared)
		return(1);
	(*shared)->philo_num = ft_atoi(argv[1]);
	(*shared)->time_to_die = ft_atoi(argv[2]);
	(*shared)->time_to_eat =ft_atoi(argv[3]);
	(*shared)->time_to_sleep = ft_atoi(argv[4]);
	if(argc == 6)
		(*shared)->must_eat_count = ft_atoi(argv[5]);
	else
		(*shared)->must_eat_count = -1;
	(*shared)->someone_died = 0;
    (*shared)->start_time_ms = 43; // you’ll implement this later
    //(*shared)->start_time_ms = get_time_ms(); // you’ll implement this later
    //pthread_mutex_init(&(*shared)->print_mutex, NULL);
    return (0);
}
int init_forks(int nb_philo, t_shared *shared)
{
    int i;

    // Allocate array of mutexes
    shared->forks = malloc(sizeof(pthread_mutex_t) * nb_philo);
    if (!shared->forks)
        return (1);

    // initi each fork mutex
    i = 0;
    while (i < nb_philo)
    {
        if (pthread_mutex_init(&shared->forks[i], NULL) != 0)
            return (1); // failed mutex init
        i++;
    }

    // Also init print mutex (only 1, no malloc)
    if (pthread_mutex_init(&shared->print_mutex, NULL) != 0)
        return (1);

    return (0);
}