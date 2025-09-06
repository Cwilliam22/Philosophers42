/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:07:00 by wcapt             #+#    #+#             */
/*   Updated: 2025/09/06 11:22:05 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_infos	*infos;

	if (argc != 5 && argc != 6)
		return (print_error(RED "Error in the number of argument \nTry again !"
				RESET "\n", -1, NULL, 2), 1);
	if (!parse(argv))
		return (print_error(RED "Input pas OK" RESET "\n", -1, NULL, 2), 1);
	infos = init_infos(argv);
	if (!infos)
		return (1);
	if (!start_simulation(infos))
	{
		clean_all(infos);
		return (print_error(RED "Simulation failed" RESET
				"\n", -1, NULL, 1), 1);
	}
	if (!clean_all(infos))
		return (print_error(RED "Clean simulation failed" RESET
				"\n", -1, NULL, 1), 1);
	return (0);
}
