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

void		print_log(pthread_mutex_t *mutex, int timestamp,
char *msg, t_philo *philo)
{
	char	*id;
	char	*timestamp_s;

	timestamp_s = ft_itoa(timestamp);
	id = ft_itoa(philo->id + 1);
	if (!philo->vars->death)
	{
		pthread_mutex_lock(mutex);
		ft_putstr("Философ ");
		ft_putstr(id);
		ft_putstr(" ");
		ft_putstr(msg);
		ft_putstr("\n");
		pthread_mutex_unlock(mutex);
	}
}

long		get_time_diff(struct timeval start, pthread_mutex_t *mutex)
{
	struct timeval now;

	pthread_mutex_lock(mutex);
	gettimeofday(&now, NULL);
	pthread_mutex_unlock(mutex);
	return (((now.tv_sec - start.tv_sec) * 1000) +
	((now.tv_usec - start.tv_usec) * 0.001));
}

void		sleep_for(long on_time, pthread_mutex_t *mutex)
{
	struct timeval start;

	pthread_mutex_lock(mutex);
	gettimeofday(&start, NULL);
	pthread_mutex_unlock(mutex);
	while (get_time_diff(start, mutex) < on_time)
		usleep(8);
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
