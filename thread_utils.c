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
void *monitor_routine(void *arg)
{
    t_shared *shared = (t_shared *)arg;
    long now;
    long time_since_meal;
    int i;

    while (!shared->someone_died)
    {
        now = get_time_ms();
        i = 0;
        while (i < shared->philo_num && !shared->someone_died)
        {
            time_since_meal = now - shared->philos[i].last_meal_time;
            if (time_since_meal > shared->time_to_die)
            {
                pthread_mutex_lock(&shared->print_mutex);
                printf("%ld %d died 💀\n",
                       now - shared->start_time_ms,
                       shared->philos[i].id);
                pthread_mutex_unlock(&shared->print_mutex);
				
                shared->someone_died = 1;
                return (NULL);
            }
            i++;
        }
        if (all_philos_ate_enough(shared))
        {
            shared->someone_died = 1;
            return NULL;
        }
        usleep(500);
    }
    return NULL;
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