/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_related.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:44:20 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/25 16:28:17 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arguments_error(void)
{
	printfd(2, "the program expects the following:\n./philo ");
	printfd(2, "%s<%snumber_of_philosophers%s>%s ", BLUE, GREEN, BLUE,
		RESET);
	printfd(2, "%s<%stime_to_die%s> %s ", BLUE, GREEN, BLUE, RESET);
	printfd(2, "%s<%stime_to_eat%s> %s ", BLUE, GREEN, BLUE, RESET);
	printfd(2, "%s<%stime_to_sleep%s> %s ", BLUE, GREEN, BLUE, RESET);
	printfd(2, "%s<%s(opt):[Number of Meals]%s> %s\n", BLUE, GREEN, BLUE,
		RESET);
	printfd(2, "the program expects 4 or 5 arguments\n");
	printfd(2, RED"please make sure that:\n"RESET);
	printfd(2, "1. the number of philosophers is between 1 and 200\n");
	printfd(2, "2. the time to die, eat and sleep are greater than 60ms\n");
	printfd(2, "4. the arguments are positive integers\n");
	printfd(2, "5. the arguments are not empty\n");
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
