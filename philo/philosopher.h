/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdolzi <rdolzi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:28:00 by rdolzi            #+#    #+#             */
/*   Updated: 2023/06/18 11:52:11 by rdolzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

//philo message
#define FORK "has taken a fork"
#define EAT "is eating"
#define SLEEP "is sleeping"
#define THINK "is thinking"
#define DIE "died"

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
    int is_eating;
    int eat_count;
    int next_fork;
    u_int64_t time_left;
    u_int64_t origin_time;
    pthread_t   philo;
    pthread_t   supervisor;
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
    int game_on;
    u_int64_t origin_time;
    pthread_mutex_t lock;
    t_philo *tavolo;
} t_env;

int init(t_env *env, int argc, char **argv);
int	ft_atoi(const char *str);
u_int64_t   get_time();
void	my_usleep(int ms);
int case_one(t_env *env);
void play(t_env *env);
#endif