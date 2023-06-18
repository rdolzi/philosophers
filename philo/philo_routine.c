/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdolzi <rdolzi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:28:15 by rdolzi            #+#    #+#             */
/*   Updated: 2023/06/18 19:02:04 by rdolzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void    message(t_philo *philo, char *str)
{
    u_int64_t time;

    time = get_time() - philo->env->origin_time;
    if (philo->is_alive  && philo->env->game_on)
        printf("%llu %d %s\n", time, philo->id + 1, str);
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
    my_usleep(philo->env->time_to_eat);
    philo->eat_count++;
    philo->is_eating = 0;
    pthread_mutex_unlock(&philo->fork);
    pthread_mutex_unlock(&philo->env->tavolo[philo->next_fork].fork);
}

void    die_all(t_env *env)
{
    int i;

    i = -1;
    while (++i < env->number_of_philosophers)
        env->tavolo[i].is_alive = 0;
}

void    *ft_supervisor(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    while (get_time() < philo->time_left)
     ;
    //printf("\nX\n");
    if (philo->env->max_eat > 0)
    {
        // printf("\nY\n");
        while (philo->eat_count < philo->env->max_eat)
            ;
    }
     if (philo->eat_count == philo->env->max_eat)
        philo->is_alive = 0;
    else{
        pthread_mutex_lock(&philo->env->lock);
        message(philo, DIE);
        die_all(philo->env);
        pthread_mutex_unlock(&philo->env->lock);
    }
    return ((void *)0);
}

void *routine(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    philo->time_left = philo->env->time_to_die + get_time();
    if (philo->id % 2 != 0)
        my_usleep(10);
    pthread_create(&philo->supervisor, NULL, &ft_supervisor, data);
    pthread_detach(philo->supervisor);
    while (philo->is_alive && philo->env->game_on)
    {
        eat(philo);
        message(philo, SLEEP);
        my_usleep(philo->env->time_to_sleep);
        message(philo, THINK);
    }
    return ((void *)0);
}


int case_one(t_env *env)
{
    message(&env->tavolo[0], FORK);
    my_usleep(env->time_to_die);
    message(&env->tavolo[0], DIE);
    free(env->tavolo);
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
        pthread_join(env->tavolo[i].philo, NULL);
    free(env->tavolo);
}
