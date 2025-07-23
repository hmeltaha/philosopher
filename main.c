/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hala <hala@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:17:43 by hala              #+#    #+#             */
/*   Updated: 2025/07/22 18:40:26 by hala             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int is_numeric(char *str)
{
    int i = 0;

    if (!str || !str[0]) // empty
        return (1);

    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (1);
        i++;
    }

    return (0);
}

int handle_input(int argc, char **argv)
{
    int     i;
    
    if(argc != 5 || argc != 6)
    return(1);
    i = 1;
    while(i < argc)
    
        if(!is_numeric(argv[i]))
            return(1);
        i++;
}   
    
        
    


int main(int argc, char **argv)
{
    int		result;
	result = handle_errors(argc, argv);
	if (result == 1)
		return (1);
}


./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
number_of_philosophers → must be > 0

time_to_die, time_to_eat, time_to_sleep → must be > 0 (in ms)

number_of_times_each_philosopher_must_eat (optional) → must be > 0

So first, you just:
✅ Read argc & argv
✅ Validate they are numbers
✅ Store them in a struct