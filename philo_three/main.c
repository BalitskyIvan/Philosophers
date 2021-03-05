/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmallado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 19:34:13 by lmallado          #+#    #+#             */
/*   Updated: 2020/12/04 19:34:16 by lmallado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*death_catcher(void *philo_struct)
{
	t_philo			*philo;
	int				i;

	i = 0;
	philo = (t_philo *)philo_struct;
	while (!philo->death && philo->eat_num != philo->number_must_eat)
	{
		sem_wait(philo->eat_lock);
		if (get_time_diff(philo->last_eat, philo->time_lock) >
		philo->time_to_die)
		{
			philo->death = 1;
			print_log(philo->write_lock,
				RED, "died", philo);
			while (i < philo->philosophers_count)
			{
				sem_post(philo->waiter);
				sem_post(philo->semaphore);
				i++;
			}
		}
		sem_post(philo->eat_lock);
	}
	return (NULL);
}

static void	die_process(t_vars *philo_struct, t_philo *philo, int id)
{
	int	i;

	i = 0;
	pthread_join(philo->death_thread, NULL);
	if (philo->death)
		sem_post(philo_struct->kill_lock);
	if (id == philo_struct->philo_count - 1 && philo->number_must_eat != -1)
	{
		while (i < philo_struct->philo_count - 1)
		{
			waitpid(philo_struct->philos[i]->philo_process, 0, 0);
			i++;
		}
		sem_post(philo_struct->kill_lock);
	}
}

static void	philosopher_process(t_vars *philo_struct, int id)
{
	char	*id_s;
	t_philo	*philo;

	philo = philo_struct->philos[id];
	id_s = ft_itoa(id);
	if (pthread_create(&philo->death_thread, NULL, death_catcher, philo) != 0)
		exit(0);
	while (1)
	{
		if (thinking_move(philo))
			break ;
		if (fork_move(philo, 1))
			break ;
		if (fork_move(philo, 0))
			break ;
		if (eating_move(philo))
			break ;
		if (sleeping_move(philo))
			break ;
	}
	sem_post(philo->eat_lock);
	sem_unlink(id_s);
	free(id_s);
	die_process(philo_struct, philo, id);
	exit(0);
}

static void	process_create(t_vars philo_struct)
{
	int	i;

	i = 0;
	sem_wait(philo_struct.kill_lock);
	while (i < philo_struct.philo_count)
	{
		if ((philo_struct.philos[i]->philo_process = fork()) == 0)
			philosopher_process(&philo_struct, i);
		i++;
	}
	sem_wait(philo_struct.kill_lock);
	waitpid(-1, 0, 0);
	i = 0;
	while (i < philo_struct.philo_count)
	{
		kill(philo_struct.philos[i]->philo_process, SIGKILL);
		i++;
	}
}

int			main(int argc, char **argv)
{
	t_vars	philo_struct;
	pid_t	main;
	int		i;

	philo_struct = init(argc, argv);
	if (philo_struct.philo_count == -1)
		exit(0);
	i = 0;
	if ((main = fork()) == 0)
	{
		process_create(philo_struct);
		exit(0);
	}
	else
	{
		waitpid(main, 0, 0);
		detach(&philo_struct);
	}
	exit(0);
}
