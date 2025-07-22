/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_related.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:44:20 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/25 18:55:57 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arguments_error(void)
{
	printfd(2, RED "\nPhilo expects the following:\n" RESET);
	printfd(2, "1. The number of philosophers\n");
	printfd(2, "2. The time a philosopher must eat before or they die\n");
	printfd(2, "3. The time each philosopher spends while eating\n");
	printfd(2, "4. The time each philosopher spends sleeping\n");
	printfd(2, "5. The number of meals a philos must eat to stop(opt)\n");
	printfd(2, RED "\nplease make sure that:\n" RESET);
	printfd(2, "1. The number of philosophers is between 1 and 200\n");
	printfd(2, "2. The time to die, eat and sleep are greater than 60ms\n");
	printfd(2, "4. The arguments are positive integers\n");
	printfd(2, "5. The arguments are not empty\n\n");
	return (ERROR);
}

// int	arguments_check(int ac, char **av)
// {
// 	int	i;

// 	i = 1;
// 	if (ac == 6 && ft_atol(av[5]) <= 0)
// 		return (ERROR);
// 	if (ft_atol(av[i]) < 1 || ft_atol(av[i]) > 200 || ft_atol(av[i]) < 0)
// 		return (ERROR);
// 	while (++i < 5)
// 	{
// 		if (ft_atol(av[i]) < 60)
// 			return (ERROR);
// 	}
// 	return (SUCCESS);
// }

// int	check_input(int ac, char **av)
// {
// 	int	i;

// 	i = 1;
// 	while (i < ac)
// 	{
// 		if (non_numeric_found(av[i]))
// 			return (ERROR);
// 	}
// 	if (arguments_check(ac, av))
// 		return (ERROR);
// 	return (0);
// }

int	argument_checkers(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (non_numeric_found(av[i]) || ft_atol(av[i]) == INT_MIN)
		{
			if (ft_atol(av[i]) == INT_MIN)
				return (printfd(2, RED "Int Overflow Detected.\n" RESET),
					ERROR);
			return (arguments_error(), ERROR);
		}
		if ((i != 5 && i != 1 && ft_atol(av[i]) == 0))
			return (arguments_error(), ERROR);
		i++;
	}
	return (SUCCESS);
}
