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

		pthread_mutex_lock(&philo->mutex[0]);
		// ft_putstr("philo_thread count\n");
		ft_putstr(ft_itoa(philo->id));
		ft_putstr("\n");

		if (i >= 10000)
		{
			pthread_mutex_unlock(&philo->mutex[0]);
		//	ft_putstr("philo_thread count\n");
			return NULL;
		}
		i++;
		pthread_mutex_unlock(&philo->mutex[0]);
	}
	return NULL;
}

int		main(int argc, char **argv)
{
	t_vars	philo_struct;

	ft_putstr("before\n");
	philo_struct = init(argc, argv, philosopher);
	//ft_putstr("after\n");

	if (philo_struct.philo_count == -1)
		return (0);
	detach(&philo_struct);
	return (0);
}
