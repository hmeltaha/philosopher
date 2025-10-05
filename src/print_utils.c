/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hala <hala@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:44:08 by hmeltaha          #+#    #+#             */
/*   Updated: 2025/08/18 04:44:32 by hala             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, const char *action)
{
	t_color		c;
	const char	*color;
	long		timestamp;

	c.colors[0] = RED;
	c.colors[1] = GREEN;
	c.colors[2] = YELLOW;
	c.colors[3] = BLUE;
	c.colors[4] = MAGENTA;
	c.colors[5] = CYAN;
	c.colors[6] = WHITE;
	c.count = 7;
	c.reset = RESET;
	timestamp = get_time_ms() - philo->shared->start_time_ms;
	pthread_mutex_lock(&philo->shared->print_mutex);
	if (!philo->shared->someone_died)
	{
		color = c.colors[(philo->id - 1) % c.count];
		printf("%s%ld %d %s%s\n", color, timestamp, philo->id, action, c.reset);
	}
	pthread_mutex_unlock(&philo->shared->print_mutex);
}
