/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdolzi <rdolzi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:28:15 by rdolzi            #+#    #+#             */
/*   Updated: 2023/06/21 20:14:29 by rdolzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	eat(t_philo *philo)
{
	sem_wait(philo->env->sem_fork);
	message(philo, FORK);
	sem_wait(philo->env->sem_fork);
	message(philo, FORK);
	philo->time_left = get_time();
	philo->is_eating = 1;
	message(philo, EAT);
	my_usleep(philo->env->time_to_eat);
	philo->eat_count++;
	philo->is_eating = 0;
	sem_post(philo->env->sem_fork);
	sem_post(philo->env->sem_fork);
}

void	die_all(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->number_of_philosophers)
		env->philo.is_alive = 0;
}

void	*ft_supervisor(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->time_left = get_time();
	while (get_time() - philo->time_left < (u_int64_t) philo->env->time_to_die
		&& (philo->env->max_eat == -1 || philo->eat_count
			< philo->env->max_eat))
		usleep(100);
	if (philo->eat_count == philo->env->max_eat)
		philo->is_alive = 0;
	else
	{
		message(philo, DIE);
		exit(3);
	}
	return ((void *)0);
}

void	play(t_env *env, int i)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		env->philo.id = i;
		if (env->philo.id % 2 != 0 && env->number_of_philosophers > 1)
			my_usleep(10);
		pthread_create(&env->philo.supervisor, NULL,
			&ft_supervisor, &env->philo);
		pthread_detach(env->philo.supervisor);
		while (env->philo.is_alive)
		{
			eat(&env->philo);
			message(&env->philo, SLEEP);
			my_usleep(env->time_to_sleep);
			message(&env->philo, THINK);
		}
		sem_close(env->sem_fork);
		exit(0);
	}
	else
		env->pid[i] = pid;
}
