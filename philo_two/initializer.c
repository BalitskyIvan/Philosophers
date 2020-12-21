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

static int				init_semaphore(int philosophers_count, t_vars *vars)
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

static t_philo			**init_philosophers(int philosophers_count,
t_vars *philo_struct, void *philosopher, t_philo philo_set)
{
	int				i;
	t_philo			**philo;

	i = 0;
	if (!(philo_struct->thread_id = malloc(sizeof(pthread_t) *
	philosophers_count)))
		return (NULL);
	if (!(philo = malloc(sizeof(t_philo*) * philosophers_count)))
	{
		detach_mutex(philo_struct);
		detach_threads(philo_struct->thread_id, i);
		return (NULL);
	}
	while (i < philosophers_count)
	{
		if (!(philo[i] = philo_dup(philo_set, i, philo_struct)))
			return (detach_set(philo_struct, philo, i));
		if (pthread_create(&philo_struct->thread_id[i], NULL,
		philosopher, philo[i]) != 0)
			return (detach_set(philo_struct, philo, i));
		i++;
	}
	return (philo);
}

static int				parse_args(t_philo *philo, char **argv, int argc)
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

static t_philo			**parse_vars(int argc, char **argv,
void *philosopher, t_vars *philo_struct)
{
	t_philo philo;
	t_philo **philos;

	if (argc == 5 || argc == 6)
	{
		if (!parse_args(&philo, argv, argc))
			return (print_error(1));
		if (!init_semaphore(philo.philosophers_count, philo_struct))
			return (print_error(2));
		philo_struct->philo_count = philo.philosophers_count;
		philo_struct->death = 0;
		philo_struct->is_death_printed = 0;
		if (!(philos = init_philosophers(philo.philosophers_count,
		philo_struct, philosopher, philo)))
			return (print_error(3));
		return (philos);
	}
	return (print_error(4));
}

t_vars					init(int argc, char **argv,
void *philosopher, t_global *global)
{
	t_vars	philo_struct;

	if (!(global->philo = parse_vars(argc, argv, philosopher,
	&philo_struct)))
		philo_struct.philo_count = -1;
	return (philo_struct);
}
