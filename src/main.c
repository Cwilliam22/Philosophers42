/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:07:00 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/08 19:46:43 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_infos	infos;

	if (argc == 5 || argc == 6)
	{
		if (!parse(argv))
			return (printf("\033[31mInput pas OK \033[0m\n"), 1);
		if (!init_all(&infos, argv))
			return (printf("\033[31mInit fail \033[0m\n"), 1);
		// Solve
		// Free
		return (printf("\033[32mInput OK \033[0m\n"), 0);
	}
	return (printf("\033[31mInput pas OK \033[0m\n"), 1);
}
