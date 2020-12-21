/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmallado <lmallado@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 00:13:51 by lmallado          #+#    #+#             */
/*   Updated: 2020/05/23 01:04:23 by lmallado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int		n_size(long n, int isminus)
{
	int i;

	i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	if (isminus == 1)
		i++;
	return (i);
}

static char		*dup_str(int is)
{
	char *res;

	if (is)
	{
		res = malloc(sizeof(char) * 11);
		res = "-2147483648";
		return (res);
	}
	else
	{
		res = malloc(sizeof(char) * 2);
		res[0] = '0';
		res[1] = '\0';
		return (res);
	}
}

static char		*to_char(int isminus, int i, long n, int size)
{
	char *res;

	if (!(res = malloc((n_size(n, isminus) + 1) * sizeof(char))))
		return (NULL);
	if (isminus == 1)
		res[0] = '-';
	res[i + size] = '\0';
	while (n > 0)
	{
		res[i + size - 1] = n % 10 + '0';
		n /= 10;
		size--;
	}
	return (res);
}

char			*ft_itoa(long n)
{
	int		i;
	int		isminus;

	i = 0;
	if (n == -2147483648)
		return (dup_str(1));
	if (n == 0)
		return (dup_str(0));
	isminus = 0;
	if (n < 0)
	{
		i++;
		isminus = 1;
		n *= -1;
	}
	return (to_char(isminus, i, n, n_size(n, 0)));
}
