/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdolzi <rdolzi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:28:00 by rdolzi            #+#    #+#             */
/*   Updated: 2023/06/20 18:18:46 by rdolzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

// philo message
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

struct	s_env;

typedef struct s_philo
{
	int				id;
	int				is_alive;
	int				is_eating;
	int				eat_count;
	u_int64_t		time_left;
	pthread_t		philo;
	pthread_t		supervisor;
	struct s_env	*env;
}	t_philo;

typedef struct s_env
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	u_int64_t		origin_time;
	sem_t			*sem_fork;
	sem_t			*sem_lock;
	pthread_mutex_t	lock;
	t_philo			philo;
}	t_env;

int			init(t_env *env, int argc, char **argv);
int			ft_atoi(const char *str);
u_int64_t	get_time(void);
void		my_usleep(int ms);
int			case_one(t_env *env);
void		play(t_env *env, int i);
void		message(t_philo *philo, char *str);
#endif