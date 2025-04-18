/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_related.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:44:20 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/18 18:24:42 by asoudani         ###   ########.fr       */
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
	return (ERROR);
}

int	arguments_check(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac == 6 && ft_atol(av[5]) <= 0)
		return (ERROR);
	if (ft_atol(av[i]) < 1 || ft_atol(av[i]) > 200)
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
		if (NonNumericFound(av[i]))
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
			return (printf(RED "At Least 2 Philos Needed\n" RESET), ERROR);
		if (ft_atol(av[1]) > 200)
			return (printf("The Number of Philos Should be Below 200\n"),
				ERROR);
		if (NonNumericFound(av[i]))
			return (arguments_error(), ERROR);
		if ((i != 5 && ft_atol(av[i]) == 0))
			return (printf("Please Provide a Valid Input.\n"), ERROR);
		if ((i != 1 && i != 5) && ft_atol(av[i]) < 60)
			return (printf("Time Values Should be Above 60ms.\n"));
		i++;
	}
	return (SUCCESS);
}
