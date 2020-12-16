/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detach.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmallado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:24:44 by lmallado          #+#    #+#             */
/*   Updated: 2020/12/07 15:24:46 by lmallado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_philo	**detach_set(t_vars *philo_struct, t_philo philo_set,
t_philo **philo, int i)
{
	free_philo(philo, i);
	detach_mutex(philo_set.mutex, i);
	detach_threads(philo_struct->thread_id, i);
	return (NULL);
}

void	detach_threads(pthread_t *thread_id, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_join(thread_id[i], NULL);
		i++;
	}
	free(thread_id);
}

void	detach_mutex(pthread_mutex_t *mutex, int size)
{
	int	i;

	i = 0;
	while (i <= size)
	{
		pthread_mutex_destroy(&mutex[i]);
		i++;
	}
	free(mutex);
}

void	free_philo(t_philo **philo, int size)
{
	int	i;

	i = 0;
	while (i <= size)
	{
		free(philo[i]);
		i++;
	}
	free(philo);
}

void	detach(t_vars *philo_struct, t_global *global)
{
	pthread_mutex_destroy(&philo_struct->get_time_mutex);
	detach_threads(philo_struct->thread_id, philo_struct->philo_count);
	detach_mutex(philo_struct->mutex, philo_struct->philo_count);
	free_philo(global->philo, philo_struct->philo_count);
}
