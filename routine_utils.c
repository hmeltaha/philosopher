/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeltaha <hmeltaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:44:35 by hmeltaha          #+#    #+#             */
/*   Updated: 2025/08/14 17:22:51 by hmeltaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


bool	all_philos_ate_enough(t_shared *shared)
{
    int	i;

	i = 0;
    if (shared->must_eat_count == -1)
        return (false);

    while (i < shared->philo_num)
    {
        if (shared->philos[i].meals_eaten < shared->must_eat_count)
            return (false);  // someone still hungry
        i++;
    }
    return (true);
}
void mutex_destroy_all(pthread_t **threads, t_shared **shared)
{
    pthread_mutex_destroy(&(*shared)->print_mutex);
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
	//destroy all mutextwe
	mutex_destroy_all(threads, shared);
    // free philos & threads (must dereference!)
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

