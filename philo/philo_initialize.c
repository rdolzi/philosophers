/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_initialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdolzi <rdolzi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:27:46 by rdolzi            #+#    #+#             */
/*   Updated: 2023/06/18 11:05:51 by rdolzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


//  1      2                      3            4          5             (6)
// ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

int ft_usleep(useconds_t time)
{
    u_int64_t start;

    start = get_time();
    while ((get_time() - start) < time)
        usleep(time / 10);
    return (0);
}

void	my_usleep(int ms)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < (u_int64_t) ms)
		usleep(ms / 10);
}


u_int64_t   get_time()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / (u_int64_t)1000));
}


int check_input(int argc, char **argv)
{
    if (ft_atoi(argv[1]) <= 0)
        return (1);
    int i = 1;
    while (++i < argc)
    {
     if (ft_atoi(argv[i]) < 0)
            return (1);
    }
    return (0);
}

void    init_philo(t_env *env, int i)
{
    env->tavolo[i].id = i;
    env->tavolo[i].is_alive = 1;
    env->tavolo[i].is_eating = 0;
    env->tavolo[i].eat_count = 0;
    env->tavolo[i].env = env;
    env->tavolo[i].origin_time = get_time();
    if (i == env->number_of_philosophers - 1)
        env->tavolo[i].next_fork = 0;
    else
        env->tavolo[i].next_fork = i + 1;
    pthread_mutex_init(&env->tavolo[i].fork, NULL);
}

int init(t_env *env, int argc, char **argv)
{
    int i;

    if(check_input(argc, argv))
        return (1);
    env->game_on = 1;
    env->number_of_philosophers = ft_atoi(argv[1]);
    env->time_to_die = ft_atoi(argv[2]);
    env->time_to_eat = ft_atoi(argv[3]);
    env->time_to_sleep = ft_atoi(argv[4]);
    env->origin_time = get_time();
    env->tavolo = (t_philo *) malloc(sizeof(t_philo) * env->number_of_philosophers);
    if (argc == 6)
        env->max_eat = ft_atoi(argv[5]);
    else
        env->max_eat = -1;
    i = -1;
    while (++i < env->number_of_philosophers)
        init_philo(env, i);
    return (0);
}
