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

static int	unlock_mutex(sem_t *write_lock, char *msg,
char *id, char *timestamp_s)
{
	if (msg[0] != 'd')
		sem_post(write_lock);
	free(id);
	free(timestamp_s);
	return (1);
}

static void	put_msg(char *msg, char *timestamp_s, char *id, char *color)
{
	ft_putstr(color);
	ft_putstr(timestamp_s);
	ft_putstr(" ");
	ft_putstr(id);
	ft_putstr(" ");
	ft_putstr(msg);
	ft_putstr(RESET);
	ft_putstr("\n");
}

int			print_log(sem_t *write_lock, char *color,
char *msg, t_philo *philo)
{
	char	*id;
	char	*timestamp_s;

	timestamp_s = ft_itoa(get_time_diff(philo->started_at,
	philo->time_lock));
	id = ft_itoa(philo->id + 1);
	if (philo->death && (msg[0] != 'd' || philo->death_printed))
		return (0);
	sem_wait(write_lock);
	if (!philo->death || (msg[0] == 'd' && !philo->death_printed))
	{
		if (msg[0] == 'd')
		{
			philo->death_printed = 1;
			philo->death = 1;
		}
		put_msg(msg, timestamp_s, id, color);
	}
	return (unlock_mutex(write_lock, msg, id, timestamp_s));
}

long		get_time_diff(struct timeval start, sem_t *time_lock)
{
	struct timeval now;

	sem_wait(time_lock);
	gettimeofday(&now, NULL);
	sem_post(time_lock);
	return (((now.tv_sec - start.tv_sec) * 1000) +
	((now.tv_usec - start.tv_usec) * 0.001));
}

void		sleep_for(long on_time, sem_t *time_lock)
{
	struct timeval start;

	sem_wait(time_lock);
	gettimeofday(&start, NULL);
	sem_post(time_lock);
	while (get_time_diff(start, time_lock) < on_time)
		usleep(8);
}
