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
# include <sys/time.h>


typedef struct		s_vars
{
	pthread_t		*thread_id;
	pthread_mutex_t	*mutex;
	int				philo_count;
	int				death;
}					t_vars;

typedef struct		s_forks
{
	int				first;
	int				second;
}					t_forks;

typedef struct		s_philo
{
	int				id;
	int				philosophers_count;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				number_must_eat;
	t_vars			*vars;
	struct timeval	last_eat;
	pthread_mutex_t	*mutex;
}					t_philo;

t_vars				init(int argc, char **argv, void *philosopher);
int					ft_atoi(const char *str);
void				ft_putstr(char *s);
void				detach(t_vars *philo_struct);
char				*ft_itoa(int n);
t_philo				*philo_dup(t_philo philo_struct, int id, t_vars *vars);
long				get_time_diff(struct timeval start);
t_forks				get_mutex_id(int id, int philosophers_count);
void				sleep_for(long on_time);
int					sleeping_move(t_philo *philo);
int					eating_move(t_philo *philo, t_forks forks);
int					fork_move(t_philo *philo, int fork_id, int is_first_fork);
int					thinking_move(t_philo *philo);
void				print_log(pthread_mutex_t *mutex, int philo_id, char *msg, t_philo *philo);

#endif