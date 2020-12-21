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

static void	unlock_mutex(pthread_mutex_t *mutex, char *id, char *timestamp_s)
{
	pthread_mutex_unlock(mutex);
	free(id);
	free(timestamp_s);
}

void		print_log(pthread_mutex_t *mutex, char *color,
char *msg, t_philo *philo)
{
	char	*id;
	char	*timestamp_s;

	timestamp_s = ft_itoa(get_time_diff(philo->started_at,
	&philo->vars->get_time_mutex));
	id = ft_itoa(philo->id + 1);
	pthread_mutex_lock(mutex);
	if (!philo->vars->death || (msg[0] == 'd' &&
	!philo->vars->is_death_printed))
	{
		if (msg[0] == 'd')
		{
			philo->vars->is_death_printed = 1;
			philo->vars->death = 1;
		}
		ft_putstr(color);
		ft_putstr(timestamp_s);
		ft_putstr(" ");
		ft_putstr(id);
		ft_putstr(" ");
		ft_putstr(msg);
		ft_putstr(RESET);
		ft_putstr("\n");
	}
	unlock_mutex(mutex, id, timestamp_s);
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
		if (id == philosophers_count)
			forks.second = 0;
		else
			forks.second = id;
		forks.first = id - 1;
	}
	return (forks);
}
