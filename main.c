/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hala <hala@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:17:43 by hala              #+#    #+#             */
/*   Updated: 2025/07/26 02:43:03 by hala             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



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

            // Uncomment for debug:
            // printf("[DEBUG] Philosopher %d time since last meal: %ld ms\n", shared->philos[i].id, time_since_meal);

            if (time_since_meal > shared->time_to_die)
            {
                pthread_mutex_lock(&shared->print_mutex);
                printf("%ld %d died 💀\n",
                       now - shared->start_time_ms,
                       shared->philos[i].id);
                pthread_mutex_unlock(&shared->print_mutex);

                shared->someone_died = 1;
                return NULL; // Stop monitor
            }
            i++;
        }

        if (all_philos_ate_enough(shared))
        {
            shared->someone_died = 1; // Signal to stop simulation
            return NULL;
        }

        usleep(500); // Sleep 0.5 ms to reduce CPU usage but keep good responsiveness
    }
    return NULL;
}



int init_all(t_shared **shared, pthread_t **threads, t_philo **philos, int argc, char **argv)
{
    int nb_philos;

    if (handle_input(argc, argv))
        return (1);
    if (init_shared(shared, argv, argc))
        return (1);
    nb_philos = (*shared)->philo_num; // number of philosophers
    if (init_philosophers(nb_philos, threads, philos))
        return (1);
    if (init_forks(nb_philos, *shared))
        return (1);
    return (0); // all good
}



int main(int argc, char **argv)
{
    int nb_philos;
    pthread_t *threads;
    t_philo *philos;
	t_shared *shared;
     pthread_t monitor;

    if (handle_input(argc, argv) == 1)
        return (1);

    nb_philos = ft_atoi(argv[1]);
	if (init_all(&shared, &threads, &philos, argc, argv))
    {
        cleanup(&shared,&threads,&philos);
        return (1);
    }
	assigns_forks(nb_philos, &shared, &philos);
    shared->philos = philos;
    if (start_routine(nb_philos, threads, philos))
    {
        cleanup(&shared,&threads,&philos);
        return (1);
    }
    if (pthread_create(&monitor, NULL, monitor_routine, shared) != 0)
    {
        printf("Error: failed to create monitor thread\n");
        cleanup(&shared, &threads, &philos);
        return (1);
    }
    pthread_join(monitor, NULL);
    wait_philosophers(nb_philos, threads);
    cleanup(&shared, &threads, &philos);
    return (0);
}

/*
1. Validate input
2. init_all() → alloc & init everything
3. assign_forks_to_philosophers()
4. start_philosophers() → create all threads
5. monitor death (or join all if finished)
6. cleanup()
*/