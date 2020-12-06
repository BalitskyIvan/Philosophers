/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmallado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:13:59 by lmallado          #+#    #+#             */
/*   Updated: 2020/12/06 17:14:01 by lmallado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_mutex(int philosophers_count, pthread_mutex_t *mutex_dst)
{
	int i;
	pthread_mutex_t	mutex[philosophers_count];

	i = 0;
	while (i < philosophers_count)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	mutex_dst = mutex;
}

static void	init_philosophers(int philosophers_count, t_vars *philo_struct,
void *philosopher)
{
	int				i;
	pthread_t		thread_id[philosophers_count];
	int				philo_id[philosophers_count];

	while (i < philosophers_count)
	{
		philo_id[i] = i;
		pthread_create(&thread_id[i], NULL, philosopher, &philo_id[i]);
		i++;
	}
	philo_struct->philo_id = philo_id;
	philo_struct->thread_id = thread_id;
}

static void	parse_vars(int argc, char **argv, t_philo *philo)
{
	
}

t_vars	init(int argc, char **argv, void *philosopher)
{
	t_vars	philo_struct;
	t_philo	philo;

	init_mutex(philosophers_count, philo_struct->mutex);
	init_philosophers(atoi(argv[1]), &philo_struct, philosopher);
	return (philo_struct);
}