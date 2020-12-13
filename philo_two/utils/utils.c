/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmallado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 14:47:03 by lmallado          #+#    #+#             */
/*   Updated: 2020/12/07 14:47:04 by lmallado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void		ft_putstr(char *s)
{
	int		i;
	char	c;

	i = 0;
	while (s[i] != '\0')
	{
		c = s[i];
		write(1, &c, 1);
		i++;
	}
}

static int	to_skip_symbols(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\t' ||
			str[i] == '\f' ||
			str[i] == '\n' ||
			str[i] == '\r' ||
			str[i] == '\v' ||
			str[i] == ' ')
		i++;
	return (i);
}

t_philo		*philo_dup(t_philo philo_struct, int id, t_vars *vars)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	new->id = id;
	new->vars = vars;
	new->eat_num = 0;
	new->waiter = vars->waiter;
	new->semaphore = vars->semaphore;
	new->number_must_eat = philo_struct.number_must_eat;
	new->philosophers_count = philo_struct.philosophers_count;
	new->time_to_die = philo_struct.time_to_die;
	new->time_to_eat = philo_struct.time_to_eat;
	new->time_to_sleep = philo_struct.time_to_sleep;
	gettimeofday(&new->started_at, NULL);
	gettimeofday(&new->last_eat, NULL);
	sem_unlink(ft_itoa(id));
	new->eat_lock = sem_open(ft_itoa(id), O_CREAT, 0660, 1);
	return (new);
}

int			ft_atoi(const char *str)
{
	int		res;
	int		is_minus;
	int		i;

	i = 0;
	is_minus = 1;
	res = 0;
	i = to_skip_symbols(str);
	if (str[i] == '-')
		is_minus = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res += str[i] - '0';
		i++;
		if (str[i] >= '0' && str[i] <= '9')
			res *= 10;
	}
	res -= 1;
	res *= is_minus;
	res += is_minus;
	return (res);
}
