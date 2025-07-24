/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeltaha <hmeltaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:17:43 by hala              #+#    #+#             */
/*   Updated: 2025/07/24 19:26:04 by hmeltaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_shared(t_shared *shared)
{
    printf("==== Shared Simulation Settings ====\n");
    printf("Philosophers:        %d\n", shared->philo_num);
    printf("time_to_die:         %d ms\n", shared->time_to_die);
    printf("time_to_eat:         %d ms\n", shared->time_to_eat);
    printf("time_to_sleep:       %d ms\n", shared->time_to_sleep);
    if (shared->must_eat_count == -1)
        printf("must_eat_count:      unlimited\n");
    else
        printf("must_eat_count:      %d\n", shared->must_eat_count);
    printf("Simulation start:    %ld ms\n", shared->start_time_ms);
    printf("Someone died flag:   %d\n", shared->someone_died);
    printf("===================================\n");
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    printf("Hello! I am philosopher %d 🍝\n", philo->id);
    return NULL;
}

// create all philosopher threads
int start_philosophers(int nb_philos, pthread_t *threads, t_philo *philos)
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

void wait_philosophers(int nb_philos, pthread_t *threads)
{
    int i = 0;
    while (i < nb_philos)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
}

void cleanup(pthread_t *threads, t_philo *philos)
{
    free(threads);
    free(philos);
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

int		assigns_forks(int nb_philos, t_shared **g_shared, t_philo **philo)
{
	int		i;

	i = 0;
	while(i < nb_philos)
	{
		philo[i].shared = g_shared;
		philo[i]->left_fork = 
	}
}
int main(int argc, char **argv)
{
    int nb_philos;
    pthread_t *threads;
    t_philo *philos;
	t_shared *shared;

    if (handle_input(argc, argv) == 1)
        return (1);

    nb_philos = ft_atoi(argv[1]);
	if (init_all(&shared, &threads, &philos, argc, argv))
        return (1);
	if(assigns_forks(nb_philos, &shared, &philos))
		return(1);
    if (start_philosophers(nb_philos, threads, philos))
    {
        cleanup(threads, philos);
        return (1);
    }
    wait_philosophers(nb_philos, threads);
    cleanup(threads, philos);

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