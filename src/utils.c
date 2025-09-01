/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:12:18 by wcapt             #+#    #+#             */
/*   Updated: 2025/09/01 12:30:58 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static	char	*join_and_free(char *str1, char *str2)
{
	char	*result;

	if (!str1 || !str2)
	{
		free(str1);
		free(str2);
		return (NULL);
	}
	result = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (result);
}

void	print_error(char *begin, int i, char *end, int out)
{
	char	*idx;
	char	*start;
	char	*finish;

	start = ft_strdup(begin);
	if (end)
		finish = ft_strdup(end);
	if (i != -1)
	{
		idx = ft_itoa(i);
		start = join_and_free(start, idx);
	}
	if (end)
		start = join_and_free(start, finish);
	write(out, start, ft_strlen(start));
	free(start);
}
