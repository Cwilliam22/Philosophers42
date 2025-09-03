/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 21:24:51 by wcapt             #+#    #+#             */
/*   Updated: 2025/09/03 21:26:13 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	ft_sizetab_ll(long long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i += 1;
		if (n == -9223372036854775807LL - 1)
			return (20);
		n = -n;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	ft_itoa_recursive_ll(long long n, char *res, int *i)
{
	if (n < 0)
	{
		res[(*i)++] = '-';
		if (n == -9223372036854775807LL - 1)
		{
			res[(*i)++] = '9';
			n = 223372036854775808LL;
		}
		else
			n = -n;
	}
	if (n > 9)
		ft_itoa_recursive_ll(n / 10, res, i);
	res[(*i)++] = (n % 10) + '0';
}

char	*ft_itoa_ll(long long n)
{
	char	*res;
	int		len;
	int		i;

	len = ft_sizetab_ll(n);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		res[i++] = '-';
		if (n == -9223372036854775807LL - 1)
		{
			res[i++] = '9';
			n = 223372036854775808LL;
		}
		else
			n = -n;
	}
	ft_itoa_recursive_ll(n, res, &i);
	res[i] = '\0';
	return (res);
}