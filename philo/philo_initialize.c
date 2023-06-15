/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_initialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdolzi <rdolzi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:27:46 by rdolzi            #+#    #+#             */
/*   Updated: 2023/06/15 17:34:37 by rdolzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


//  1      2                      3            4          5             (6)
// ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
void ft_exit(t_env *env, int error)
{
    if (env->philo)
        free(env->philo);
    if (error)
        exit(1);
    exit(0);
}

int check_input(int argc, char **argv)
{
    if ()
}

void init(t_env *env, int argc, char **argv)
{
    if(!check_input(argc, argv))
        ft_exit(env, 1);
    env->number_of_philosophers = ft_atoi(argv[1]);
    env->time_to_die = ft_atoi(argv[2]);
    env->time_to_eat = ft_atoi(argv[3]);
    env->time_to_sleep = ft_atoi(argv[4]);
    env->philo = (t_philo *) malloc(sizeof(t_philo) * env->number_of_philosophers);
    if (argc == 6)
        env->max_eat = ft_atoi(argv[5]);
    else
        env->max_eat = -1;
    init_philo(env);
}