/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeltaha <hmeltaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:11:55 by hala              #+#    #+#             */
/*   Updated: 2025/07/24 19:20:28 by hmeltaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

// think → pick forks → eat → sleep
typedef struct s_shared
{	
	int philo_num;         // number of philosophers
	int time_to_die;       // max time before a philosopher dies without eating
	int time_to_eat;
	int time_to_sleep;     // how long a philosopher sleeps
	int must_eat_count;
	long start_time_ms; 
	int someone_died;              // stop flag (e.g. someone died)
	pthread_mutex_t  print_mutex;       // mutex to synchronize console output (optional but important)
	pthread_mutex_t *forks;
	
} t_shared;

typedef struct s_philo
{
    int         id;             // philosopher number
    int         meals_so_far;   // how many times this philosopher ate
    long        last_meal_time; // timestamp of last meal
    pthread_t   thread_id;      // its thread id
    pthread_mutex_t *left_fork; // pointer to left fork mutex
    pthread_mutex_t *right_fork;// pointer to right fork mutex
    t_shared   *shared;         // pointer to the shared simulation data
} t_philo;



//main.c
int main(int argc, char **argv);
	
//utils
int is_numeric(char *str);
int handle_input(int argc, char **argv);
long	ft_atol(const char *nptr);
 // initi
int init_philosophers(int nb_philos, pthread_t **threads, t_philo **philos);
int init_shared(t_shared **shared, char **argv, int argc);
int init_forks(int nb_philo, t_shared *shared);




#endif
