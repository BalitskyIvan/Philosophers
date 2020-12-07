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

#include "philo.h"

void	ft_putstr(char *s)
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
