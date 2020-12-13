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

static void	detach_threads(t_vars *philo_struct)
{
	int	i;

	i = 0;
	while (i < philo_struct->philo_count)
	{
		pthread_join(philo_struct->thread_id[i], NULL);
		i++;
	}
	free(philo_struct->thread_id);
}

static void	detach_mutex(t_vars *philo_struct)
{
	sem_close(philo_struct->semaphore);
	sem_close(philo_struct->waiter);
	sem_close(philo_struct->time_lock);
	sem_close(philo_struct->write_lock);
	sem_unlink("semaphore");
	sem_unlink("waiter");
	sem_unlink("time_lock");
	sem_unlink("write_lock");
}

void		detach(t_vars *philo_struct)
{
	detach_threads(philo_struct);
	detach_mutex(philo_struct);
}
