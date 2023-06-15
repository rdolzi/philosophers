/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdolzi <rdolzi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:28:00 by rdolzi            #+#    #+#             */
/*   Updated: 2023/06/15 16:49:00 by rdolzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <pthread.h>

typedef struct s_philo
{
    int id;
    int origin_time;
    int eat_count;
    pthread_mutex_t fork;
    t_env *env;
} t_philo;

typedef struct s_env
{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int max_eat;
    pthread_t *philo;
} t_env;

void init(t_env *env, int argc, char **argv);

#endif