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

static int	init_semaphore(int philosophers_count, t_vars *vars)
{
	sem_unlink("semaphore");
	sem_unlink("waiter");
	sem_unlink("time_lock");
	sem_unlink("write_lock");
	if ((vars->semaphore =
	sem_open("semaphore", O_CREAT, 0660, philosophers_count)) == SEM_FAILED)
		return (0);
	if ((vars->waiter =
	sem_open("waiter", O_CREAT, 0660, 1)) == SEM_FAILED)
		return (0);
	if ((vars->time_lock =
	sem_open("time_lock", O_CREAT, 0660, 1)) == SEM_FAILED)
		return (0);
	if ((vars->write_lock =
	sem_open("write_lock", O_CREAT, 0660, 1)) == SEM_FAILED)
		return (0);
	return (1);
}

static int	init_philosophers(int philosophers_count,
t_vars *philo_struct, t_philo philo_set)
{
	int	i;

	i = 0;
	if (!(philo_struct->philos = malloc(sizeof(pid_t *) * philosophers_count)))
		return (0);
	while (i < philosophers_count)
	{
		if (!(philo_struct->philos[i] = philo_dup(philo_set, i, philo_struct)))
		{
			detach_philos(philo_struct, i);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	parse_args(t_philo *philo, char **argv, int argc)
{
	philo->id = 0;
	if ((philo->philosophers_count = ft_atoi(argv[1])) < 1)
		return (0);
	if ((philo->time_to_die = ft_atoi(argv[2])) < 1)
		return (0);
	if ((philo->time_to_eat = ft_atoi(argv[3])) < 1)
		return (0);
	if ((philo->time_to_sleep = ft_atoi(argv[4])) < 1)
		return (0);
	if (argc == 6)
	{
		if ((philo->number_must_eat = ft_atoi(argv[5])) < 1)
			return (0);
	}
	else
		philo->number_must_eat = -1;
	philo->eat_num = 0;
	return (1);
}

static int	parse_vars(int argc, char **argv, t_vars *philo_struct)
{
	t_philo philo;

	if (argc == 5 || argc == 6)
	{
		if (!parse_args(&philo, argv, argc))
			return (print_error(1));
		if (!init_semaphore(philo.philosophers_count, philo_struct))
			return (print_error(2));
		if (!init_philosophers(philo.philosophers_count, philo_struct, philo))
			return (print_error(3));
		return (philo.philosophers_count);
	}
	return (print_error(4));
}

t_vars		init(int argc, char **argv)
{
	t_vars	philo_struct;

	philo_struct.philo_count = parse_vars(argc, argv, &philo_struct);
	return (philo_struct);
}
