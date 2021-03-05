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
	if (!philo->death)
		if (!print_log(philo->write_lock,
		MAG,
		"is thinking", philo))
			return (1);
	return (philo->death);
}

int	fork_move(t_philo *philo, int is_first_fork)
{
	if (!philo->death)
	{
		sem_wait(philo->eat_lock);
		if (is_first_fork)
			sem_wait(philo->waiter);
		sem_post(philo->eat_lock);
		if (philo->death)
			return (1);
		sem_wait(philo->eat_lock);
		sem_wait(philo->semaphore);
		sem_post(philo->eat_lock);
		if (!print_log(philo->write_lock, YEL,
		"has taken a fork", philo))
			return (1);
	}
	return (philo->death);
}

int	eating_move(t_philo *philo)
{
	if (!philo->death)
	{
		sem_post(philo->waiter);
		sem_wait(philo->time_lock);
		gettimeofday(&philo->last_eat, NULL);
		sem_post(philo->time_lock);
		if (!print_log(philo->write_lock, GRN,
		"is eating", philo))
			return (1);
		philo->eat_num++;
		sem_wait(philo->eat_lock);
		sleep_for(philo->time_to_eat, philo->time_lock);
		sem_post(philo->eat_lock);
		sem_post(philo->semaphore);
		sem_post(philo->semaphore);
		if (philo->eat_num == philo->number_must_eat)
			return (1);
	}
	return (philo->death);
}

int	sleeping_move(t_philo *philo)
{
	if (!philo->death && philo->eat_num != philo->number_must_eat)
	{
		if (!print_log(philo->write_lock,
		BLU, "is sleeping", philo))
			return (1);
		sleep_for(philo->time_to_sleep, philo->time_lock);
	}
	return (philo->death);
}
