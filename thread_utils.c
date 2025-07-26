#include "philo.h"

long get_time_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
 
//function ---1
void wait_philosophers(int nb_philos, pthread_t *threads)
{
    int i = 0;
    while (i < nb_philos)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
}
//function ---2
void assigns_forks(int nb_philos, t_shared **g_shared, t_philo **philo)
{
    int i = 0;
    while (i < nb_philos)
    {
        (*philo)[i].shared = *g_shared;
        (*philo)[i].left_fork = &(*g_shared)->forks[i];
        if (nb_philos == 1)
            (*philo)[i].right_fork = NULL;
        else
            (*philo)[i].right_fork = &(*g_shared)->forks[(i + 1) % nb_philos];
        i++;
    }
}

// void safe_print(t_philo *philo, const char *msg)
// {
//     pthread_mutex_lock(&philo->shared->print_mutex);
//     printf("%ld %d %s\n",
//         get_time_ms() - philo->shared->start_time_ms,
//         philo->id,
//         msg);
//     pthread_mutex_unlock(&philo->shared->print_mutex);
// }