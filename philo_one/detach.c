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

#include "philo.h"

void	detach(t_vars *philo_struct)
{
	int	i;

	i = 0;
	while (i < philo_struct->philo_count)
	{
		pthread_join(philo_struct->thread_id[i], NULL);
		//pthread_mutex_destroy(&philo_struct->mutex[i]);
		i++;
	}
}