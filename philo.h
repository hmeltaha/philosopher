/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeltaha <hmeltaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:11:55 by hala              #+#    #+#             */
/*   Updated: 2025/08/20 18:54:20 by hmeltaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

// think → pick forks → eat → sleep
typedef struct s_shared
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				stopped;
	_Atomic int		must_eat_count;
	long			start_time_ms;
	_Atomic int		someone_died;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	must_eat_mutex;
	pthread_mutex_t	someone_died_mutex;
	struct s_philo	*philos;
}					t_shared;

typedef struct s_philo
{
	int				id;
	int				meals_so_far;
	_Atomic long	last_meal_time;
	_Atomic int		meals_eaten;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_shared		*shared;
}					t_philo;

typedef struct s_color
{
	const char		*colors[7];
	int				count;
	const char		*reset;
}					t_color;

// main.c
int					main(int argc, char **argv);

// utils
int					is_numeric(char *str);
int					handle_input(int argc, char **argv);
long				ft_atol(const char *nptr);
int					init_all(t_shared **shared, pthread_t **threads,
						t_philo **philos, char **argv);
int					get_argv(char **argv);

// initi
int					init_philosophers(int nb_philos, pthread_t **threads,
						t_philo **philos);
int					init_shared(t_shared **shared, char **argv, int argc);
int					init_forks(int nb_philo, t_shared *shared);

// routine.c
int					start_routine(int nb_philos, pthread_t *threads,
						t_philo *philos);
void				*philo_routine_even(void *arg);
void				*philo_routine(void *arg);
void				think(t_philo *philo);
void				eat(t_philo *philo);
void				sleep_philo(t_philo *philo);
void				eat_meal(t_philo *philo, pthread_mutex_t *l,
						pthread_mutex_t *r);
int					lock_forks(t_philo *philo, pthread_mutex_t *l,
						pthread_mutex_t *r);

// thread_utils
long				get_time_ms(void);
void				wait_philosophers(int nb_philos, pthread_t *threads);
void				assigns_forks(int nb_philos, t_shared **g_shared,
						t_philo **philo);
void				*monitor_routine(void *arg);

// print_utils
void				print_action(t_philo *philo, const char *action);
// routine_utils
void				cleanup(t_shared **shared, pthread_t **threads,
						t_philo **philos);
bool				all_philos_ate_enough(t_shared *shared);
// libft_utils
int					ft_atoi(const char *nptr);
int					ft_isdigit(int digit);
#endif
