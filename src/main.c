/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt <wcapt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:07:00 by wcapt             #+#    #+#             */
/*   Updated: 2025/08/28 14:42:11 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_infos	*infos;

	infos = malloc(sizeof(*infos));
	if (argc == 5 || argc == 6)
	{
		if (!parse(argv))
			return (printf(RED "Input pas OK" RESET "\n"), 1);
		infos = init_infos(argv);
		//if (!init_all(infos, argv))
		//	return (printf(RED "Init fail" RESET "\n"), 1);
		// Solve
		// Free
		return (printf(GREEN "Input OK" RESET "\n"), 0);
	}
	printf(RED "Error in the number of argument \nTry again !\n" RESET "\n"); 
	return (1);
}
