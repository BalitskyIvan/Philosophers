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
		print_log(&philo->mutex[philo->philosophers_count],
		philo->id, "думает...", philo);
	return (philo->vars->death);
}

int	fork_move(t_philo *philo, int fork_id, int is_first_fork)
{
	if (!philo->vars->death)
	{
		pthread_mutex_lock(&philo->mutex[fork_id]);
		if (!philo->vars->death)
		{
			if (is_first_fork)
				print_log(&philo->mutex[philo->philosophers_count],
				philo->id, "взял первую вилку", philo);
			else
				print_log(&philo->mutex[philo->philosophers_count],
				philo->id, "взял вторую вилку", philo);
		}
	}
	return (philo->vars->death);
}

int	eating_move(t_philo *philo, t_forks forks)
{
	if (!philo->vars->death)
	{
		pthread_mutex_lock(&philo->vars->get_time_mutex);
		gettimeofday(&philo->last_eat, NULL);
		pthread_mutex_unlock(&philo->vars->get_time_mutex);
		print_log(&philo->mutex[philo->philosophers_count],
		philo->id, "кушает", philo);
		sleep_for(philo->time_to_eat, &philo->vars->get_time_mutex);
		pthread_mutex_unlock(&philo->mutex[forks.first]);
		pthread_mutex_unlock(&philo->mutex[forks.second]);
		philo->eat_num++;
	}
	return (philo->vars->death);
}

int	sleeping_move(t_philo *philo)
{
	if (!philo->vars->death)
	{
		print_log(&philo->mutex[philo->philosophers_count],
		philo->id, "лег спать", philo);
		sleep_for(philo->time_to_sleep, &philo->vars->get_time_mutex);
	}
	return (philo->vars->death);
}
