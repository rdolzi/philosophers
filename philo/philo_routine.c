/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdolzi <rdolzi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:28:15 by rdolzi            #+#    #+#             */
/*   Updated: 2023/06/20 23:51:19 by rdolzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	message(philo, FORK);
	pthread_mutex_lock(&philo->env->tavolo[philo->next_fork].fork);
	message(philo, FORK);
	philo->is_eating = 1;
	philo->time_left += philo->env->time_to_die;
	message(philo, EAT);
	my_usleep(philo->env->time_to_eat);
	philo->eat_count++;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->env->tavolo[philo->next_fork].fork);
}

void	die_all(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->number_of_philosophers)
		env->tavolo[i].is_alive = 0;
}

void	*ft_supervisor(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (get_time() < philo->time_left && (philo->env->max_eat
			== -1 || philo->eat_count < philo->env->max_eat))
		;
	if (philo->env->max_eat > 0 && philo->eat_count >= philo->env->max_eat)
		philo->is_alive = 0;
	else
	{
		pthread_mutex_lock(&philo->env->lock);
		message(philo, DIE);
		die_all(philo->env);
		pthread_mutex_unlock(&philo->env->lock);
	}
	return ((void *)0);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->time_left = philo->env->time_to_die + get_time();
	if (philo->id % 2 != 0 && philo->env->number_of_philosophers > 1)
		my_usleep(10);
	if (pthread_create(&philo->supervisor, NULL, &ft_supervisor, data))
		return ((void *)1);
	pthread_detach(philo->supervisor);
	while (philo->is_alive)
	{
		if (philo->env->number_of_philosophers == 1)
			case_one(philo->env);
		else
		{
			eat(philo);
			message(philo, SLEEP);
			my_usleep(philo->env->time_to_sleep);
			message(philo, THINK);
		}
	}
	if (pthread_join(philo->supervisor, NULL))
		return ((void *)1);
	return ((void *)0);
}

int	play(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->number_of_philosophers)
	{
		if (pthread_create(&env->tavolo[i].philo, NULL, &routine, (
					void *)&env->tavolo[i]))
			return (1);
	}
	i = -1;
	while (++i < env->number_of_philosophers)
	{
		if (pthread_join(env->tavolo[i].philo, NULL))
			return (1);
	}
	free(env->tavolo);
	return (0);
}
