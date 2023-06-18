/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdolzi <rdolzi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:27:39 by rdolzi            #+#    #+#             */
/*   Updated: 2023/06/17 23:17:30 by rdolzi           ###   ########.fr       */
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
// 1)STOPPARE TUTTI SE MUORE UNO
// 2)PER STOPPARE IL MAX_EAT
// nel supervisor di ogni philo: se ha fatto tutti i pasti fa max_eat--
// se max_eat == terminare tutti i processi
// probabilmente settando un altra variabile(on/off)
// che nel while termina tutti i philo
// 3)controllo if error sui pthread()
// 4)non va il loop ./philo 5 800 200 200 200
int main (int argc, char **argv)
{
	t_env env;

    if (argc < 5 || argc > 6)
        return (1);
    if (init(&env, argc, argv))
		return (1);
	if (env.number_of_philosophers == 1)
		return (case_one(&env));
    play(&env);
    return (0);
}