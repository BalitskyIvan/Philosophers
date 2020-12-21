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
		if (get_time_diff(philo->last_eat, &philo->vars->get_time_mutex) >
		philo->time_to_die || philo->eat_num == philo->number_must_eat)
		{
			pthread_mutex_lock(&philo->eat_lock);
			philo->vars->death = 1;
			print_log(&philo->mutex[philo->philosophers_count],
				RED, "died", philo);
			while (i < philo->philosophers_count)
			{
				pthread_mutex_unlock(&philo->mutex[i]);
				i++;
			}
		}
	}
	pthread_mutex_unlock(&philo->eat_lock);
	return (NULL);
}

void	*philosopher(void *philo_struct)
{
	t_philo			*philo;
	t_forks			forks;
	pthread_t		death_thread;

	philo = (t_philo *)philo_struct;
	forks = get_mutex_id(philo->id, philo->philosophers_count);
	pthread_create(&death_thread, NULL, death_catcher, philo_struct);
	while (1)
	{
		if (thinking_move(philo))
			break ;
		if (fork_move(philo, forks.first, 1))
			break ;
		if (fork_move(philo, forks.second, 0))
			break ;
		if (eating_move(philo, forks))
			break ;
		if (sleeping_move(philo))
			break ;
	}
	pthread_join(death_thread, NULL);
	pthread_mutex_destroy(&philo->eat_lock);
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
