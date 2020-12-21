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

void	*death_catcher(void *philo_struct)
{
	t_philo			*philo;
	int				i;

	i = 0;
	philo = (t_philo *)philo_struct;
	while (!philo->vars->death)
	{
		sem_wait(philo->eat_lock);
		if (get_time_diff(philo->last_eat, philo->vars->time_lock) >
		philo->time_to_die || philo->eat_num == philo->number_must_eat)
		{
			philo->vars->death = 1;
			print_log(philo->vars->write_lock,
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

void	*philosopher(void *philo_struct)
{
	t_philo			*philo;
	pthread_t		death_thread;
	char			*id_s;

	philo = (t_philo *)philo_struct;
	id_s = ft_itoa(philo->id);
	pthread_create(&death_thread, NULL, death_catcher, philo);
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
	pthread_join(death_thread, NULL);
	sem_close(philo->eat_lock);
	sem_unlink(id_s);
	return (NULL);
}

int		main(int argc, char **argv)
{
	t_vars		philo_struct;
	t_global	global;

	philo_struct = init(argc, argv, philosopher, &global);
	if (philo_struct.philo_count == -1)
		return (0);
	detach(&philo_struct, &global);
	return (0);
}
