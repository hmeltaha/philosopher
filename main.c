/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hala <hala@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:17:43 by hala              #+#    #+#             */
/*   Updated: 2025/07/24 01:51:33 by hala             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int pthread_create(pthread_t *restrict thread,const pthread_attr_t *restrict attr,
                          void *(*start_routine)(void *),
                          void *restrict arg);

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    printf("Hello! I am philosopher %d 🍝\n", philo->id);
    return NULL;
}

int main(int argc, char **argv)
{
    int nb_philos;
    pthread_t *threads;
    t_philo *philos;
    int i;

    if (handle_input(argc, argv) == 1)
        return (1);
    nb_philos = ft_atoi(argv[1]);
    threads = malloc(sizeof(pthread_t) * nb_philos);
    philos = malloc(sizeof(t_philo) * nb_philos);
    if (!threads || !philos)
        return (1);

    // ✅ create all threads
    i = 0;
    while (i < nb_philos)
    {
        philos[i].id = i + 1;
        pthread_create(&threads[i], NULL, philo_routine, &philos[i]);
        i++;
    }

    // ✅ join all threads
    i = 0;
    while (i < nb_philos)
    {
        pthread_join(threads[i], NULL);
        i++;
    }

    free(threads);
    free(philos);

    return (0);
}
