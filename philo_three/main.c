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
	while (!philo->death)
	{
		sem_wait(philo->eat_lock);
		if (get_time_diff(philo->last_eat, philo->time_lock) >
		philo->time_to_die || philo->eat_num == philo->number_must_eat)
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

static void	philosopher_process(t_philo *philo)
{
	pthread_create(&philo->death_thread, NULL, death_catcher, philo);
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
	sem_unlink(ft_itoa(philo->id));
	pthread_join(philo->death_thread, NULL);
	exit(0);
}

int			main(int argc, char **argv)
{
	t_vars	philo_struct;
	int		i;

	i = 0;
	philo_struct = init(argc, argv);
	if (philo_struct.philo_count == -1)
		return (0);
	while (i < philo_struct.philo_count)
	{
		if ((philo_struct.philos[i]->philo_process = fork()) == 0)
			philosopher_process(philo_struct.philos[i]);
		i++;
	}
	wait_process_end(&philo_struct);
	detach(&philo_struct);
	return (0);
}
