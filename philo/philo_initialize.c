/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_initialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdolzi <rdolzi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:27:46 by rdolzi            #+#    #+#             */
/*   Updated: 2023/06/20 14:23:59 by rdolzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	my_usleep(int ms)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < (u_int64_t)ms)
		usleep(ms / 10);
}

u_int64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / (u_int64_t)1000));
}

int	check_input(int argc, char **argv)
{
	int	i;

	i = 1;
	if (ft_atoi(argv[1]) <= 0)
		return (1);
	while (++i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
			return (1);
	}
	return (0);
}

void	init_philo(t_env *env, int i)
{
	env->tavolo[i].id = i;
	env->tavolo[i].is_alive = 1;
	env->tavolo[i].is_eating = 0;
	env->tavolo[i].eat_count = 0;
	env->tavolo[i].env = env;
	if (i == env->number_of_philosophers - 1)
		env->tavolo[i].next_fork = 0;
	else
		env->tavolo[i].next_fork = i + 1;
	pthread_mutex_init(&env->tavolo[i].fork, NULL);
}

int	init(t_env *env, int argc, char **argv)
{
	int	i;

	if (check_input(argc, argv))
		return (1);
	env->number_of_philosophers = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	env->origin_time = get_time();
	env->tavolo = (t_philo *)malloc(sizeof(
				t_philo) * env->number_of_philosophers);
	pthread_mutex_init(&env->lock, NULL);
	if (argc == 6)
		env->max_eat = ft_atoi(argv[5]);
	else
		env->max_eat = -1;
	i = -1;
	while (++i < env->number_of_philosophers)
		init_philo(env, i);
	return (0);
}
