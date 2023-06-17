/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdolzi <rdolzi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:28:15 by rdolzi            #+#    #+#             */
/*   Updated: 2023/06/17 21:29:18 by rdolzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"



void    message(t_philo *philo, char *str)
{
    
}
// prende le due forchette
// mangia (mentre mangia is_eating == 1)
// aggiorna il time_to_die
// posa le forchette
void eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->fork);
    message(philo, FORK);
    pthread_mutex_lock(&philo->env->tavolo[philo->next_fork].fork);
    message(philo, FORK);
    philo->is_eating = 1;
    message(philo, EAT);
    philo->eat_count++;
    my_usleep(philo->env->time_to_eat);
    philo->is_eating = 0;
    pthread_mutex_unlock(&philo->fork);
    pthread_mutex_unlock(&philo->env->tavolo[philo->next_fork].fork);
}

void routine(void *data)
{
    t_philo *philo;
    
    philo = (t_philo *) data;
    if (philo->id % 2 != 0)
        my_usleep(10);
    while (philo->is_alive)
    {
        eat(philo);
        message(philo, SLEEP);
        my_usleep(philo->env->time_to_sleep);
        message(philo, THINK);
    }
}

int case_one(t_env *env)
{
    message(&env->tavolo[0], FORK);
    my_usleep(env->time_to_die);
    message(&env->tavolo[0], DIE);
    free(env->tavolo);
    // pthread_create(&env->tavolo[0].philo, NULL, &routine, (void *)&env->tavolo[0]);
    // pthread_join(&env->tavolo[0].philo, NULL);
    return (0);
}

void    play(t_env *env)
{
    int i;

    i = -1;
    while (++i < env->number_of_philosophers)
        pthread_create(&env->tavolo[i].philo, NULL, &routine, (void *)&env->tavolo[i]);
    i = -1;
    while (++i < env->number_of_philosophers)
        pthread_join(&env->tavolo[i].philo, NULL);
    free(env->tavolo);
}