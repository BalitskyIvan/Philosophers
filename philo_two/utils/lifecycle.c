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

#include "../philo.h"

int	thinking_move(t_philo *philo)
{
	if (!philo->vars->death)
		print_log(philo->vars->write_lock,
		MAG,
		"is thinking", philo);
	return (philo->vars->death);
}

int	fork_move(t_philo *philo, int is_first_fork)
{
	if (!philo->vars->death)
	{
		if (is_first_fork)
			sem_wait(philo->waiter);
		sem_wait(philo->semaphore);
		if (!philo->vars->death)
		{
			if (is_first_fork)
				print_log(philo->vars->write_lock, YEL,
				"has taken a second fork", philo);
			else
				print_log(philo->vars->write_lock, YEL,
				"has taken a first fork", philo);
		}
	}
	return (philo->vars->death);
}

int	eating_move(t_philo *philo)
{
	if (!philo->vars->death)
	{
		sem_post(philo->waiter);
		sem_wait(philo->vars->time_lock);
		gettimeofday(&philo->last_eat, NULL);
		sem_post(philo->vars->time_lock);
		print_log(philo->vars->write_lock, GRN,
		"is eating", philo);
		philo->eat_num++;
		sem_wait(philo->eat_lock);
		sleep_for(philo->time_to_eat, philo->vars->time_lock);
		sem_post(philo->eat_lock);
		sem_post(philo->semaphore);
		sem_post(philo->semaphore);
	}
	return (philo->vars->death);
}

int	sleeping_move(t_philo *philo)
{
	if (!philo->vars->death && philo->eat_num != philo->number_must_eat)
	{
		print_log(philo->vars->write_lock,
		BLU, "is sleeping", philo);
		sleep_for(philo->time_to_sleep, philo->vars->time_lock);
	}
	return (philo->vars->death);
}
