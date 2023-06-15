/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdolzi <rdolzi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:27:39 by rdolzi            #+#    #+#             */
/*   Updated: 2023/06/15 16:52:02 by rdolzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

//  1      2                      3            4          5             (6)
// ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
int main (int argc, char **argv)
{
    t_env env;

    if (argc < 5 || argc > 6)
        return (1);
    init(&env, argc, argv);
    play(&env);
    return (0);
}