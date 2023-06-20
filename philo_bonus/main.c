/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdolzi <rdolzi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:27:39 by rdolzi            #+#    #+#             */
/*   Updated: 2023/06/20 23:14:14 by rdolzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	message(t_philo *philo, char *str)
{
	u_int64_t	time;

	time = get_time() - philo->env->origin_time;
	if (philo->is_alive)
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

void	kill_em_all(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->number_of_philosophers)
		kill(env->pid[i], SIGKILL);
}

int	main(int argc, char **argv)
{
	t_env	env;
	int		i;
	int		status;

	i = -1;
	sem_unlink("/semfork");
	if (argc < 5 || argc > 6)
		return (1);
	if (init(&env, argc, argv))
		return (1);
	while (++i < env.number_of_philosophers)
		play(&env, i);
	i = -1;
	while (++i < env.number_of_philosophers)
	{
		waitpid(-1, &status, 0);
		if (WSTOPSIG(status) == 3)
			kill_em_all(&env);
	}
	sem_close(env.sem_fork);
	return (0);
}
