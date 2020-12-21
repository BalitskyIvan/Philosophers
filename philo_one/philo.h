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

# define RESET "\033[0m"
# define RED "\x1B[31m"
# define GRN "\x1B[32m"
# define YEL "\x1B[33m"
# define BLU "\x1B[34m"
# define MAG "\x1B[35m"

typedef struct		s_vars
{
	pthread_t		*thread_id;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	get_time_mutex;
	int				philo_count;
	int				death;
	int				is_death_printed;
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
	int				eat_num;
	t_vars			*vars;
	struct timeval	last_eat;
	struct timeval	started_at;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	*mutex;
}					t_philo;

typedef struct		s_global
{
	int				philo_count;
	t_philo			**philo;
}					t_global;

t_vars				init(int argc, char **argv, void *philosopher,
t_global *global);
int					ft_atoi(const char *str);
void				ft_putstr(char *s);
void				detach(t_vars *philo_struct, t_global *global);
char				*ft_itoa(long n);
t_philo				*philo_dup(t_philo philo_struct, int id, t_vars *vars);
long				get_time_diff(struct timeval start, pthread_mutex_t *mutex);
t_forks				get_mutex_id(int id, int philosophers_count);
void				sleep_for(long on_time, pthread_mutex_t *mutex);
int					sleeping_move(t_philo *philo);
int					eating_move(t_philo *philo, t_forks forks);
int					fork_move(t_philo *philo, int fork_id, int is_first_fork);
int					thinking_move(t_philo *philo);
void				print_log(pthread_mutex_t *mutex, char *color, char *msg,
t_philo *philo);
t_philo				**print_error(int id);
void				free_philo(t_philo **philo, int size);
void				detach_mutex(pthread_mutex_t *mutex, int size);
void				detach_threads(pthread_t *thread_id, int size);
t_philo				**detach_set(t_vars *philo_struct, t_philo philo_set,
t_philo **philo, int i);

#endif
