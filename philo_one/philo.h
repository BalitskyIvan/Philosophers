/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmallado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 19:34:47 by lmallado          #+#    #+#             */
/*   Updated: 2020/12/04 19:34:49 by lmallado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct		s_vars
{
	pthread_t		*thread_id;
	pthread_mutex_t	*mutex;
	int				philo_count;
}					t_vars;

typedef struct		s_philo
{
	int				id;
	int				philosophers_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_must_eat;
	pthread_mutex_t	*mutex;
}					t_philo;

t_vars				init(int argc, char **argv, void *philosopher);
int					ft_atoi(const char *str);
void				ft_putstr(char *s);
void				detach(t_vars *philo_struct);

#endif