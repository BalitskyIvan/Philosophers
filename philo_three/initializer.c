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

static void	init_semaphore(int philosophers_count, t_vars *vars)
{
	sem_unlink("semaphore");
	sem_unlink("waiter");
	sem_unlink("time_lock");
	sem_unlink("write_lock");
	vars->semaphore = sem_open("semaphore", O_CREAT, 0660, philosophers_count);
	vars->waiter = sem_open("waiter", O_CREAT, 0660, 1);
	vars->time_lock = sem_open("time_lock", O_CREAT, 0660, 1);
	vars->write_lock = sem_open("write_lock", O_CREAT, 0660, 1);
}

static void	init_philosophers(int philosophers_count,
t_vars *philo_struct, t_philo philo_set)
{
	int	i;

	i = 0;
	philo_struct->philos = malloc(sizeof(pid_t *) * philosophers_count);
	while (i < philosophers_count)
	{
		philo_struct->philos[i] = philo_dup(philo_set, i, philo_struct);
		i++;
	}
}

static int	parse_vars(int argc, char **argv, t_vars *philo_struct)
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
		init_semaphore(philo.philosophers_count, philo_struct);
		init_philosophers(philo.philosophers_count, philo_struct, philo);
		return (philo.philosophers_count);
	}
	else
		ft_putstr("Wrong number of arguments, sorry :(\n");
	return (-1);
}

t_vars		init(int argc, char **argv)
{
	t_vars	philo_struct;

	philo_struct.philo_count = parse_vars(argc, argv, &philo_struct);
	return (philo_struct);
}
