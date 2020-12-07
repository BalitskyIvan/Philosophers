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
void *philosopher, t_philo *philo_set)
{
	int				i;
	pthread_t		thread_id[philosophers_count];
	t_philo			*philo[philosophers_count];

	while (i < philosophers_count)
	{
		philo[i] = philo_set;
		philo[i]->id = i;
		pthread_create(&thread_id[i], NULL, philosopher, philo[i]);
		i++;
	}
	philo_struct->thread_id = thread_id;
}

static int	parse_vars(int argc, char **argv, void *philosopher, t_vars *philo_struct)
{
	t_philo philo;

	philo.id = -1;
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
		init_mutex(philo.philosophers_count, philo.mutex);
		init_philosophers(philo.philosophers_count, philo_struct, philosopher, &philo);
		return(philo.philosophers_count);
	}
	else
		ft_putstr("Wrong number of arguments, sorry :(\n");
	return (-1);
}

t_vars	init(int argc, char **argv, void *philosopher)
{
	t_vars	philo_struct;

	philo_struct.philo_count = parse_vars(argc, argv, philosopher, &philo_struct);
	ft_putstr("init succes\n");
	return (philo_struct);
}