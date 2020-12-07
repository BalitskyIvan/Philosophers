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

void	*philosopher(void *philo_struct)
{
	t_philo *philo;
	philo = (t_philo *) philo_struct;
	int i = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex[philo->id]);
		if (i >= 10000)
		{
			pthread_mutex_unlock(&philo->mutex[philo->id]);
			printf("philo_thread %d count %d\n", philo->id, i);
			return NULL;
		}
		pthread_mutex_unlock(&philo->mutex[philo->id]);

		i++;
	}
	return NULL;
}

int		main(int argc, char **argv)
{
	t_vars	philo_struct;

	philo_struct = init(argc, argv, philosopher);
	if (philo_struct.philo_count)
		return (0);
	detach(&philo_struct);
	return (0);
}
