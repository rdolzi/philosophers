/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdolzi <rdolzi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:28:15 by rdolzi            #+#    #+#             */
/*   Updated: 2023/06/16 23:14:47 by rdolzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


void routine(void *data)
{
    t_philo *philo;
    
    philo = (t_philo *) data;
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
}