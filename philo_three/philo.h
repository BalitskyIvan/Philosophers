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
# include <semaphore.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <signal.h>

# define RESET "\033[0m"
# define RED "\x1B[31m"
# define GRN "\x1B[32m"
# define YEL "\x1B[33m"
# define BLU "\x1B[34m"
# define MAG "\x1B[35m"

typedef struct		s_philo
{
	int				id;
	int				philosophers_count;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				number_must_eat;
	int				eat_num;
	pid_t			philo_process;
	struct timeval	last_eat;
	struct timeval	started_at;
	sem_t			*semaphore;
	pthread_t		death_thread;
	sem_t			*waiter;
	sem_t			*eat_lock;
	sem_t			*write_lock;
	sem_t			*time_lock;
	int				death;
	int				death_printed;
}					t_philo;

typedef struct		s_vars
{
	sem_t			*semaphore;
	sem_t			*waiter;
	sem_t			*time_lock;
	sem_t			*write_lock;
	t_philo			**philos;
	int				philo_count;
}					t_vars;

t_vars				init(int argc, char **argv);
int					ft_atoi(const char *str);
void				ft_putstr(char *s);
void				detach(t_vars *philo_struct);
char				*ft_itoa(long n);
t_philo				*philo_dup(t_philo philo_struct, int id, t_vars *vars);
long				get_time_diff(struct timeval start, sem_t *mutex);
void				sleep_for(long on_time, sem_t *mutex);
int					sleeping_move(t_philo *philo);
int					eating_move(t_philo *philo);
int					fork_move(t_philo *philo, int is_first_fork);
int					thinking_move(t_philo *philo);
void				print_log(sem_t *mutex, char *color, char *msg,
t_philo *philo);
void				wait_process_end(t_vars *philo_struct);
int					print_error(int id);
void				detach_philos(t_vars *philo_struct, int size);

#endif
