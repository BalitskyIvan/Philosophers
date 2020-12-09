/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmallado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 10:46:26 by lmallado          #+#    #+#             */
/*   Updated: 2020/12/09 10:46:31 by lmallado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void		print_log(pthread_mutex_t *mutex, int philo_id, char *msg)
{
	pthread_mutex_lock(mutex);
	ft_putstr("Философ ");
	ft_putstr(ft_itoa(philo_id + 1));
	ft_putstr(" ");
	ft_putstr(msg);
	ft_putstr("\n");
	pthread_mutex_unlock(mutex);
}

long	get_time_diff(struct timeval start)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	return (now.tv_sec - start.tv_sec);
}

void		sleep_for(long on_time)
{
	struct timeval start;

	gettimeofday(&start, NULL);
	while (get_time_diff(start) * 1000 < on_time);
}

t_forks		get_mutex_id(int id, int philosophers_count)
{
	t_forks forks;

	id++;
	if (id % 2 == 0)
	{
		if (id == philosophers_count)
			forks.first = 0;
		else
			forks.first = id;
		forks.second = id - 1;
	}
	else
	{
		forks.first = id - 1;
		if (id == philosophers_count)
			forks.second = 0;
		else
			forks.second = id;
	}
	return (forks);
}