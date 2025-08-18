/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hala <hala@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:17:43 by hala              #+#    #+#             */
/*   Updated: 2025/08/18 04:32:08 by hala             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	run_threads(int nb, t_shared *shared, pthread_t *threads, t_philo *philos)
{
	pthread_t	monitor;

	if (start_routine(nb, threads, philos))
		return (1);
	if (pthread_create(&monitor, NULL, monitor_routine, shared) != 0)
		return (1);
	pthread_join(monitor, NULL);
	wait_philosophers(nb, threads);
	return (0);
}

int	init_all(t_shared **shared, pthread_t **threads, t_philo **philos,
		char **argv)
{
	int	nb_philos;
	int	argc;

	argc = get_argv(argv);
	if (init_shared(shared, argv, argc))
		return (1);
	nb_philos = (*shared)->philo_num;
	if (init_philosophers(nb_philos, threads, philos))
		return (1);
	if (init_forks(nb_philos, *shared))
		return (1);
	assigns_forks(nb_philos, shared, philos);
	(*shared)->philos = *philos;
	return (0);
}

int	main(int argc, char **argv)
{
	int			nb_philos;
	pthread_t	*threads;
	t_philo		*philos;
	t_shared	*shared;

	if (handle_input(argc, argv))
		return (1);
	if (init_all(&shared, &threads, &philos, argv))
	{
		cleanup(&shared, &threads, &philos);
		return (1);
	}
	nb_philos = ft_atoi(argv[1]);
	if (run_threads(nb_philos, shared, threads, philos))
	{
		cleanup(&shared, &threads, &philos);
		return (1);
	}
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