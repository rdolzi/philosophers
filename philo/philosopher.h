/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdolzi <rdolzi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:28:00 by rdolzi            #+#    #+#             */
/*   Updated: 2023/06/16 22:53:00 by rdolzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

struct s_env;

typedef struct s_philo
{
    int id;
    int is_alive;
    int eat_count;
    u_int64_t origin_time;
    pthread_t   philo;
    pthread_mutex_t fork;
    struct s_env *env;
} t_philo;

typedef struct s_env
{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int max_eat;
    t_philo *tavolo;
} t_env;

int init(t_env *env, int argc, char **argv);
int	ft_atoi(const char *str);
u_int64_t   get_time();
void	my_usleep(int ms);
#endif