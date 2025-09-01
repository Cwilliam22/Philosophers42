/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:09:20 by wcapt             #+#    #+#             */
/*   Updated: 2025/09/01 19:06:36 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	valid_integer(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!ft_is_a_number(argv[i]))
		{
			print_error(RED "ERROR : ARG ", i, "is not a number" RESET "\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	max_or_min(char **argv)
{
	long int	number;
	int			i;

	i = 1;
	while (argv[i])
	{
		number = ft_atol(argv[i]);
		if (i == 1 && ft_atoi(argv[i]) > NB_MAX_PHILO)
			return (print_error(RED "ERROR : ARG ", i, " > MAX PHILO" RESET
					"\n", 2), 0);
		if (i == 1 && number < 1)
			return (print_error(RED "ERROR : ARG ", i, " < MIN PHILO" RESET
					"\n", 2), 0);
		if ((number < 0 || number > INT_MAX))
			return (print_error(RED "ERROR : ARG ", i, " > INT_MAX" RESET
					"\n", 2), 0);
		if (i != 5 && i != 1 && (number < 1 || number > INT_MAX))
			return (print_error(RED "ERROR : ARG ", i, " < 0" RESET
					"\n", 2), 0);
		i++;
	}
	return (1);
}

int	parse(char **argv)
{
	if (!max_or_min(argv))
		return (0);
	if (!valid_integer(argv))
		return (0);
	return (1);
}
