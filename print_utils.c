/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeltaha <hmeltaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:44:08 by hmeltaha          #+#    #+#             */
/*   Updated: 2025/08/13 15:44:09 by hmeltaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static const char	*philo_colors[] = {
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE};

static const int	COLOR_COUNT = sizeof(philo_colors)
	/ sizeof(philo_colors[0]);

void	print_action(t_philo *philo, const char *action)
{
	long		timestamp;
	const char	*color;

	timestamp = get_time_ms() - philo->shared->start_time_ms;
	pthread_mutex_lock(&philo->shared->print_mutex);
	// Don't print anything if someone already died
	if (!philo->shared->someone_died)
	{
		// Pick color based on philosopher ID
		color = philo_colors[(philo->id - 1) % COLOR_COUNT];
		printf("%s%ld %d %s%s\n",
				color,     // color start
				timestamp, // time
				philo->id, // philosopher id
				action,    // e.g. "is eating"
				RESET);    // reset color
	}
	pthread_mutex_unlock(&philo->shared->print_mutex);
}
