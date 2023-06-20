/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdolzi <rdolzi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:27:39 by rdolzi            #+#    #+#             */
/*   Updated: 2023/06/20 14:15:31 by rdolzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	message(t_philo *philo, char *str)
{
	u_int64_t	time;

	time = get_time() - philo->env->origin_time;
	if (philo->is_alive && philo->env->game_on)
		printf("%llu %d %s\n", time, philo->id + 1, str);
}

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
	if (res > 2147483647 || res < -2147483648)
		return (-1);
	return ((int)res * sign);
}

int	case_one(t_env *env)
{
	message(&env->tavolo[0], FORK);
	my_usleep(env->time_to_die);
	message(&env->tavolo[0], DIE);
	free(env->tavolo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_env	env;

	if (argc < 5 || argc > 6)
		return (1);
	if (init(&env, argc, argv))
		return (1);
	if (env.number_of_philosophers == 1)
		return (case_one(&env));
	play(&env);
	return (0);
}
