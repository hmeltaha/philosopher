/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hala <hala@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:11:55 by hala              #+#    #+#             */
/*   Updated: 2025/07/26 02:31:46 by hala             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>

#define RESET       "\033[0m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"

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
	struct s_philo *philos;
	
} t_shared;

typedef struct s_philo
{
    int         id;             // philosopher number
    int         meals_so_far;   // how many times this philosopher ate
    long        last_meal_time; // timestamp of last meal
	int		meals_eaten;
    pthread_t   thread_id;      // its thread id
    pthread_mutex_t *left_fork; // pointer to left fork mutex
    pthread_mutex_t *right_fork;// pointer to right fork mutex
    t_shared   *shared;         // pointer to the shared simulation data
} t_philo;



//main.c
int main(int argc, char **argv);
void *monitor_routine(void *arg);
	
//utils
int is_numeric(char *str);
int handle_input(int argc, char **argv);
long	ft_atol(const char *nptr);
 // initi
int init_philosophers(int nb_philos, pthread_t **threads, t_philo **philos);
int init_shared(t_shared **shared, char **argv, int argc);
int init_forks(int nb_philo, t_shared *shared);

//routine.c
int start_routine(int nb_philos, pthread_t *threads, t_philo *philos);
void *philo_routine(void *arg);
void    think(t_philo *philo);
void eat(t_philo *philo);
void sleep_philo(t_philo *philo);

//thread_utils
long get_time_ms(void);
void wait_philosophers(int nb_philos, pthread_t *threads);
void		assigns_forks(int nb_philos, t_shared **g_shared, t_philo **philo);
void safe_print(t_philo *philo, const char *msg);

//print_utils
void print_action(t_philo *philo, const char *action);
//routine_utils
void cleanup(t_shared **shared, pthread_t **threads, t_philo **philos);
bool all_philos_ate_enough(t_shared *shared);
#endif
