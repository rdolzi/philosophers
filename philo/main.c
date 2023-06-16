/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdolzi <rdolzi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:27:39 by rdolzi            #+#    #+#             */
/*   Updated: 2023/06/16 22:30:49 by rdolzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

//  1      2                      3            4          5             (6)
// ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

int	ft_atoi(const char *str)
{
	size_t	i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == 32)
		i++;
	if (str[i] == 45)
		sign = -1;
	if (str[i] == 43 || str[i] == 45)
		i++;
	while (str[i] >= 48 && str[i] <= 57)
		res = (res * 10) + (str[i++] - 48);
	if (str[i] != 0)
		return (-1);
    if (res > 2147483647 || res < -2147483648 )
        return (-1);
	return ((int) res * sign);
}

int main (int argc, char **argv)
{
	t_env env;

    if (argc < 5 || argc > 6)
        return (1);
    if (init(&env, argc, argv))
		return (1);
    play(&env);
    return (0);
}