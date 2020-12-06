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


void	join_threads()
{

}

int		main(int argc, char **argv)
{
	t_vars	philo_struct;

	philo_struct = init(argc, argv);
	i = 0;
	while (i < threads_count)
	{
		pthread_join(thread_id[i], NULL);
		i++;
	}
	return (0);
}
