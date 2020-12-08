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
	t_philo			*philo;

	philo = (t_philo *) philo_struct;
	while (1)
	{
		//usleep()
		pthread_mutex_lock(&philo->mutex[philo->id]);
		ft_putstr(ft_itoa(philo->id));
		ft_putstr(" diff ");
		ft_putstr(ft_itoa(get_time_diff(philo->started)));
		ft_putstr("\n");
		pthread_mutex_unlock(&philo->mutex[philo->id]);
		pthread_mutex_unlock(&philo->mutex[philo->id]);
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
