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

int		is_philo_dead = 0;

void	*philosopher(void *philo_struct)
{
	t_philo			*philo;
	t_forks			forks;

	philo = (t_philo *) philo_struct;
	forks = get_mutex_id(philo->id, philo->philosophers_count);
	while (1)
	{
		print_log(&philo->mutex[philo->philosophers_count], philo->id, "думает...");
		pthread_mutex_lock(&philo->mutex[forks.first]);
		print_log(&philo->mutex[philo->philosophers_count], philo->id, "взял первую вилку");
		pthread_mutex_lock(&philo->mutex[forks.second]);
		print_log(&philo->mutex[philo->philosophers_count], philo->id, "взял вторую вилку");
		print_log(&philo->mutex[philo->philosophers_count], philo->id, "кушает");
		sleep_for(philo->time_to_eat);
		pthread_mutex_unlock(&philo->mutex[forks.first]);
		pthread_mutex_unlock(&philo->mutex[forks.second]);
		print_log(&philo->mutex[philo->philosophers_count], philo->id, "лег спать");
		sleep_for(philo->time_to_sleep);
		if (get_time_diff(philo->started) * 1000 >= philo->time_to_die)
		{
			print_log(&philo->mutex[philo->philosophers_count], philo->id, "помер :(");
			return (NULL);
		}
	}
	return NULL;
}

int		main(int argc, char **argv)
{
	t_vars	philo_struct;

	philo_struct = init(argc, argv, philosopher);
	if (philo_struct.philo_count == -1)
		return (0);
	detach(&philo_struct);
	return (0);
}
