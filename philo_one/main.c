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

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *philosopher(void *id)
{
	int *philo_id;
	philo_id = (int *) id;
	int i = 0;
	while (1)
	{
		pthread_mutex_lock(&mutex);
		if (i >= 10000)
		{
			pthread_mutex_unlock(&mutex);
			printf("philo_thread %d count %d\n", *philo_id, i);
			return NULL;
		}
		pthread_mutex_unlock(&mutex);

		i++;
	}
	return NULL;
}

int	main(int argc, char **argv)
{
	int			threads_count;
	int 		i = 0;
	threads_count = atoi(argv[1]);
	pthread_t	thread_id[threads_count];
	int			philo_id[threads_count];

	printf("main\n");

	while (i < threads_count)
	{
		philo_id[i] = i;
		pthread_create(&thread_id[i], NULL, philosopher, &philo_id[i]);
		i++;
	}

	i = 0;
	while (i < threads_count)
	{
		pthread_join(thread_id[i], NULL);
		i++;
	}
	return (0);
}
