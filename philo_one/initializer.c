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

static pthread_mutex_t	*init_mutex(int philosophers_count)
{
	int				i;
	pthread_mutex_t	*mutex;

	i = 0;
	mutex = malloc(sizeof(pthread_mutex_t) * (philosophers_count + 1));
	while (i <= philosophers_count)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	return (mutex);
}

static void				init_philosophers(int philosophers_count,
t_vars *philo_struct, void *philosopher, t_philo philo_set)
{
	int				i;
	t_philo			*philo;

	i = 0;
	philo_struct->death = 0;
	philo_struct->thread_id = malloc(sizeof(pthread_t) * philosophers_count);
	while (i < philosophers_count)
	{
		philo = philo_dup(philo_set, i, philo_struct);
		pthread_create(&philo_struct->thread_id[i], NULL, philosopher, philo);
		i++;
	}
}

static int				parse_vars(int argc, char **argv, void *philosopher,
t_vars *philo_struct)
{
	t_philo philo;

	if (argc == 5 || argc == 6)
	{
		philo.id = 0;
		philo.philosophers_count = ft_atoi(argv[1]);
		philo.time_to_die = ft_atoi(argv[2]);
		philo.time_to_eat = ft_atoi(argv[3]);
		philo.time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			philo.number_must_eat = ft_atoi(argv[5]);
		else
			philo.number_must_eat = -1;
		philo.eat_num = 0;
		pthread_mutex_init(&philo_struct->get_time_mutex, NULL);
		philo.mutex = init_mutex(philo.philosophers_count);
		philo_struct->mutex = philo.mutex;
		init_philosophers(philo.philosophers_count, philo_struct,
		philosopher, philo);
		return (philo.philosophers_count);
	}
	else
		ft_putstr("Wrong number of arguments, sorry :(\n");
	return (-1);
}

t_vars					init(int argc, char **argv, void *philosopher)
{
	t_vars	philo_struct;

	philo_struct.philo_count = parse_vars(argc, argv, philosopher,
	&philo_struct);
	return (philo_struct);
}
