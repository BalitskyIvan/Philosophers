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
	sem_unlink("semaphore");
	sem_unlink("waiter");
	sem_unlink("time_lock");
	sem_unlink("write_lock");
}

void		wait_process_end(t_vars *philo_struct)
{
	int	i;

	waitpid(-1, 0, 0);
	i = 0;
	while (i < philo_struct->philo_count)
	{
		kill(philo_struct->philos[i]->philo_process, SIGKILL);
		i++;
	}
}

void		detach(t_vars *philo_struct)
{
	detach_mutex(philo_struct);
}
