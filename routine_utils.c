#include "philo.h"


bool all_philos_ate_enough(t_shared *shared)
{
    if (shared->must_eat_count == -1)
        return false;  // unlimited meals, never consider done
    int i = 0;

    while (i < shared->philo_num)
    {
        if (shared->philos[i].meals_eaten < shared->must_eat_count)
            return false;  // someone still hungry
        i++;
    }
    return true;
}
void cleanup(t_shared **shared, pthread_t **threads, t_philo **philos)
{
    int i = 0;

    if (!shared || !(*shared))
        return;
    if ((*shared)->forks)
    {
        while (i < (*shared)->philo_num)
        {
            pthread_mutex_destroy(&(*shared)->forks[i]);
            i++;
        }
        free((*shared)->forks);
    }
    pthread_mutex_destroy(&(*shared)->print_mutex);
    // Free philos & threads (must dereference!)
    if (philos && *philos)
    {
        free(*philos);
        *philos = NULL;
    }
    if (threads && *threads)
    {
        free(*threads); 
        *threads = NULL;
    }
    free(*shared);
    *shared = NULL;
}

