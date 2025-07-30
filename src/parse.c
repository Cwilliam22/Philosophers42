/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt <wcapt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:09:20 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/30 01:06:15 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	valid_unsigned_integer(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		printf("argv : %s\n", argv[i]);
		if (!ft_is_a_number(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	not_max_or_min(char **argv)
{
	long int	number;
	int			i;

	i = 1;
	while (argv[i])
	{
		number = ft_atol(argv[i]);
		if (number > 2147483647)
			return (0);
		if (number <= -2147483648)
			return (0);
		i++;
	}
	return (1);
}

int	parse(char **argv)
{
	if (!not_max_or_min(argv))
		return (0);
	if (!valid_unsigned_integer(argv))
		return (0);
	return (1);
}
