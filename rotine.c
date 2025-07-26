#include "philo.h"

//func -- 1
// create all philosopher threads
int start_routine(int nb_philos, pthread_t *threads, t_philo *philos)
{
    int i = 0;
    while (i < nb_philos)
    {
        philos[i].id = i + 1;
        if (pthread_create(&threads[i], NULL, philo_routine, &philos[i]) != 0)
        {
            printf("Error: failed to create thread %d\n", i + 1);
            return (1);
        }
        i++;
    }
    return (0);
}
//func -- 2
void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    philo->last_meal_time = get_time_ms();
    while (!philo->shared->someone_died)
    {
        think(philo);
        eat(philo);
        sleep_philo(philo);
    }
    return (NULL);
}
//func -- 3
void    think(t_philo *philo)
{
    print_action(philo, "is thinking");
}
//func -- 4
void eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    if (philo->shared->someone_died)
    {
        pthread_mutex_unlock(philo->left_fork);
        return;
    }
    print_action(philo, "has taken a fork");

    // If right_fork is NULL (one philosopher case), just unlock left and return (can't eat)
    if (philo->right_fork == NULL)
    {
        pthread_mutex_unlock(philo->left_fork);
        return;
    }

    pthread_mutex_lock(philo->right_fork);
    if (philo->shared->someone_died)
    {
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        return;
    }
    print_action(philo, "has taken a fork");

    philo->last_meal_time = get_time_ms();
    philo->meals_eaten++;
    print_action(philo, "is eating");

    long start = get_time_ms();
    while (!philo->shared->someone_died &&
           (get_time_ms() - start < philo->shared->time_to_eat))
    {
        usleep(100); // 0.1 ms sleep for responsiveness
    }

    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}



void sleep_philo(t_philo *philo)
{
    long start;

    start = get_time_ms();
    while (!philo->shared->someone_died &&
           (get_time_ms() - start < philo->shared->time_to_sleep))
    {
        usleep(100); // sleep 0.1ms intervals for responsiveness
    }
}



