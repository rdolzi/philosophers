/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdolzi <rdolzi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:28:15 by rdolzi            #+#    #+#             */
/*   Updated: 2023/06/20 18:21:21 by rdolzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	eat(t_philo *philo)
{
	sem_wait(philo->env->sem_fork);
	message(philo, FORK);
	sem_wait(philo->env->sem_fork);
	message(philo, FORK);
	philo->is_eating = 1;
	philo->time_left = get_time();
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
	while (get_time() - philo->time_left < (u_int64_t) philo->env->time_to_die && (philo->env->max_eat == -1 || philo->eat_count < philo->env->max_eat))
		;
	// while ((t =get_time()) < philo->time_left && i < 10 )
	// {
	// 	printf("(IN%d)t:%llu| pl:%llu\n",philo->id, t, philo->time_left);
	// 	i++;
	// }
	// ;
	// && (philo->env->max_eat
	// 		== -1 || philo->eat_count < philo->env->max_eat))
	// 	;
	// printf("(OUT%d)t:%llu| pl:%llu\n", philo->id, t, philo->time_left);

	// printf("DEBUG\n");
	// exit(0);
	if (philo->env->max_eat > 0 && philo->eat_count >= philo->env->max_eat)
		philo->is_alive = 0;
	else
	{
		printf("CIAO\n");
		sem_wait(philo->env->sem_lock);
		message(philo, DIE);
		philo->is_alive = 0;
		//die_all(philo->env);
		sem_post(philo->env->sem_lock);
	}
	return ((void *)0);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	//philo->time_left = philo->env->time_to_die + get_time();
	// if (philo->id % 2 != 0)
	// 	my_usleep(10);
	pthread_create(&philo->supervisor, NULL, &ft_supervisor, data);
	pthread_detach(philo->supervisor);
	while (philo->is_alive)
	{
		printf("ciao\n");
		exit (0);
		// eat(philo);
		// message(philo, SLEEP);
		// my_usleep(philo->env->time_to_sleep);
		// message(philo, THINK);
	}
	if (pthread_join(philo->supervisor, NULL))
		return ((void *)1);
	return ((void *)0);
}

// void	play(t_env *env)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < env->number_of_philosophers)
// 		pthread_create(&env->tavolo[i].philo, NULL, &routine, (
// 				void *)&env->tavolo[i]);
// 	i = -1;
// 	while (++i < env->number_of_philosophers)
// 		pthread_join(env->tavolo[i].philo, NULL);
// 	free(env->tavolo);
// }

void	play(t_env *env, int i)
{
	pid_t	pid;

	pid = fork();

	if (pid == 0)
	{
		env->philo.id = i;
		if (env->philo.id % 2 != 0)
			my_usleep(10);
		env->philo.time_left = env->time_to_die + get_time();
		pthread_create(&env->philo.supervisor, NULL, &ft_supervisor, &env->philo);
		pthread_detach(env->philo.supervisor);
		while (env->philo.is_alive)
		{
			eat(&env->philo);
			message(&env->philo, SLEEP);
			my_usleep(env->time_to_sleep);
			message(&env->philo, THINK);
		}
		if (pthread_join(env->philo.supervisor, NULL))
			exit(1);
		exit(0);
	}
}
