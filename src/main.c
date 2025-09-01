/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:07:00 by wcapt             #+#    #+#             */
/*   Updated: 2025/09/01 19:18:22 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_infos	*infos;

	if (argc != 5 && argc != 6)
	{
		print_error(RED "Error in the number of argument \nTry again !" RESET
			"\n", -1, NULL, 2);
		return (1);
	}
	if (!parse(argv))
		return (print_error(RED "Input pas OK" RESET "\n", -1, NULL, 2), 1);
	infos = init_infos(argv);
	//print_arg_struct_infos(infos);
	if (!start_simulation(infos))
		return (print_error(RED "Simulation failed" RESET "\n", -1, NULL, 1), 0);
	clean_all(infos);
	return (print_error(GREEN "Input OK" RESET "\n", -1, NULL, 1), 0);
}




// print les acctions des philos
// reset last_meal quand un philo mange


// Prendre les fourchettes
// Manger : mettre à jour last_meal_ms, attendre time_to_eat, incrémenter meals_eaten.
// Reposer les fourchettes.
// Dormir : attendre time_to_sleep.
// Penser : petite pause, puis on recommence.