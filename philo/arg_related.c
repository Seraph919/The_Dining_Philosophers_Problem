/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_related.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:44:20 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/20 20:45:34 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arguments_error(void)
{
	printf("the program expects the following:\n./philo ");
	printf("%s<%snumber_of_philosophers%s>%s ", BLUE, GREEN, BLUE, RESET);
	printf("%s<%stime_to_die%s> %s ", BLUE, GREEN, BLUE, RESET);
	printf("%s<%stime_to_eat%s> %s ", BLUE, GREEN, BLUE, RESET);
	printf("%s<%stime_to_sleep%s> %s ", BLUE, GREEN, BLUE, RESET);
	printf("%s<%s(opt):[Number of Meals]%s> %s\n", BLUE, GREEN, BLUE, RESET);
	printf("the program expects 4 or 5 arguments\n");
	printf(RED"please make sure that:\n"RESET);
	printf("1. the number of philosophers is between 1 and 200\n");
	printf("2. the time to die, eat and sleep are greater than 60ms\n");
	printf("4. the arguments are positive integers\n");
	printf("5. the arguments are not empty\n");
	return (ERROR);
}

int	arguments_check(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac == 6 && ft_atol(av[5]) <= 0)
		return (ERROR);
	if (ft_atol(av[i]) < 1 || ft_atol(av[i]) > 200 || ft_atol(av[i]) < 0)
		return (ERROR);
	while (++i < 5)
	{
		if (ft_atol(av[i]) < 60)
			return (ERROR);
	}
	return (SUCCESS);
}

int	check_input(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (non_numeric_found(av[i]))
			return (ERROR);
	}
	if (arguments_check(ac, av))
		return (ERROR);
	return (0);
}

int	argument_checkers(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_atol(av[1]) == 0)
			return (printf(RED "Bad input\n" RESET), ERROR);
		if (ft_atol(av[1]) > 200)
			return (printf("The Number of Philos Should be 0 < N < 200\n"),
				ERROR);
		if (non_numeric_found(av[i]) || ft_atol(av[i]) < 0)
			return (printf(RED"integer overflow detected\n"RESET), ERROR);
		if ((i != 5 && ft_atol(av[i]) == 0))
			return (printf("Please Provide a Valid Input.\n"), ERROR);
		if ((i != 1 && i != 5) && ft_atol(av[i]) < 60)
			return (printf("Time Values Should be Above 60ms.\n"));
		i++;
	}
	return (SUCCESS);
}
