/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_initialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdolzi <rdolzi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:27:46 by rdolzi            #+#    #+#             */
/*   Updated: 2023/06/20 17:33:50 by rdolzi           ###   ########.fr       */
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

void	init_philo(t_env *env)
{
	env->philo.id = 0;
	env->philo.is_alive = 1;
	env->philo.is_eating = 0;
	env->philo.eat_count = 0;
	env->philo.env = env;
}

int	init(t_env *env, int argc, char **argv)
{
	if (check_input(argc, argv))
		return (1);
	env->number_of_philosophers = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	env->origin_time = get_time();
	env->sem_fork = sem_open("sem_fork", O_CREAT, 0660, env->number_of_philosophers);
	env->sem_lock = sem_open("sem_lock", O_CREAT, 0660, 1);
	// sem_close(&env->sem_fork);
	// sem_close(&env->sem_lock);
	if (argc == 6)
		env->max_eat = ft_atoi(argv[5]);
	else
		env->max_eat = -1;
	init_philo(env);
	return (0);
}
