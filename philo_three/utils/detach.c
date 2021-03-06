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

static void	detach_mutex(t_vars *philo_struct)
{
	sem_close(philo_struct->semaphore);
	sem_close(philo_struct->waiter);
	sem_close(philo_struct->time_lock);
	sem_close(philo_struct->write_lock);
	sem_close(philo_struct->kill_lock);
	sem_unlink("semaphore");
	sem_unlink("waiter");
	sem_unlink("time_lock");
	sem_unlink("write_lock");
	sem_unlink("kill_lock");
}

void		detach_philos(t_vars *philo_struct, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		sem_unlink(ft_itoa(philo_struct->philos[i]->id));
		free(philo_struct->philos[i]);
		i++;
	}
	free(philo_struct->philos);
}

void		detach(t_vars *philo_struct)
{
	sem_post(philo_struct->write_lock);
	detach_mutex(philo_struct);
	detach_philos(philo_struct, philo_struct->philo_count);
}
