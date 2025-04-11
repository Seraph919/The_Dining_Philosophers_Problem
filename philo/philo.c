/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:25:10 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/11 14:50:12 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_unlock(philo->right_f);
}

void	update_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->mut_last_eat_time);
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&philo->mut_last_eat_time);
}

void	update_nb_meals_had(t_philo *philo)
{
	pthread_mutex_lock(&philo->mut_nb_meals_had);
	philo->nb_meals_had++;
	pthread_mutex_unlock(&philo->mut_nb_meals_had);
}

void	sleep_for_eating(t_philo *philo)
{
	ft_usleep(get_eat_time(philo->data));
}

int	eat(t_philo *philo)
{
	if (take_forks(philo) != 0)
		return (1);
	// set_philo_state(philo, EATING);
	print_msg(philo->data, philo->id, EAT);
	update_last_meal_time(philo);
	sleep_for_eating(philo);
	update_nb_meals_had(philo);
	unlock(philo);
	return (0);
}

void	drop_left_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_f);
}

void	drop_right_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_f);
}

int	take_left_fork(t_philo *philo)
{
	if (philo_died(philo) ) // || get_philo_state(philo) == DEAD
		return (1);
	// pthread_mutex_lock
	pthread_mutex_lock(philo->left_f);
	print_msg(philo->data, philo->id, TAKE_FORKS);
	return (0);
}

int	take_right_fork(t_philo *philo)
{
	if (philo_died(philo) ) // || get_philo_state(philo) == DEAD
		return (1);
	pthread_mutex_lock(philo->right_f);
	print_msg(philo->data, philo->id, TAKE_FORKS);
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (get_nb_philos(philo->data) == 1)
		return (handle_1_philo(philo));
	if (take_right_fork(philo) != 0)
		return (1);
	if (take_left_fork(philo) != 0)
	{
		drop_right_fork(philo);
		return (1);
	}
	return (0);
}

bool	get_keep_iter(t_data *data)
{
	bool	keep_iterating;

	pthread_mutex_lock(&data->mut_keep_iter);
	keep_iterating = data->keep_iterating;
	pthread_mutex_unlock(&data->mut_keep_iter);
	return (keep_iterating);
}

// int	get_nb_philos(t_data *data)
// {
// 	int	nb_philos;

// 	pthread_mutex_lock(&data->mut_nb_philos);
// 	nb_philos = data->nb_philos;
// 	pthread_mutex_unlock(&data->mut_nb_philos);
// 	return (nb_philos);
// }

// t_state	get_philo_state(t_philo *philo)
// {
// 	t_state	state;

// 	pthread_mutex_lock(&philo->mut_state);
// 	state = philo->state;
// 	pthread_mutex_unlock(&philo->mut_state);
// 	return (state);
// }

int	get_nb_meals_philo_had(t_philo *philo)
{
	int	nb_meals_had;

	pthread_mutex_lock(&philo->mut_nb_meals_had);
	nb_meals_had = philo->nb_meals_had;
	pthread_mutex_unlock(&philo->mut_nb_meals_had);
	return (nb_meals_had);
}

size_t	get_start_time(t_data *data)
{
	size_t	time;

	pthread_mutex_lock(&data->mut_start_time);
	time = data->start_time;
	pthread_mutex_unlock(&data->mut_start_time);
	return (time);
}

size_t	get_die_time(t_data *data)
{
	size_t	die_time;

	pthread_mutex_lock(&data->mut_die_t);
	die_time = data->die_time;
	pthread_mutex_unlock(&data->mut_die_t);
	return (die_time);
}

size_t	get_sleep_time(t_data *data)
{
	size_t	sleep_time;

	pthread_mutex_lock(&data->mut_sleep_t);
	sleep_time = data->sleep_time;
	pthread_mutex_unlock(&data->mut_sleep_t);
	return (sleep_time);
}

size_t	get_eat_time(t_data *data)
{
	size_t	eat_time;

	pthread_mutex_lock(&data->mut_eat_t);
	eat_time = data->eat_time;
	pthread_mutex_unlock(&data->mut_eat_t);
	return (eat_time);
}

size_t	get_last_eat_time(t_philo *philo)
{
	size_t	last_eat_time;

	pthread_mutex_lock(&philo->mut_last_eat_time);
	last_eat_time = philo->last_eat_time;
	pthread_mutex_unlock(&philo->mut_last_eat_time);
	return (last_eat_time);
}

int	init_forks(t_data *data)
{
	int		i;
	t_philo	*philos;

	philos = data->philos;
	i = -1;
	while (++i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (ERROR);
	}
	i = 0;
	philos[0].left_f = &data->forks[0];
	philos[0].right_f = &data->forks[data->nb_philos - 1];
	while (++i < data->nb_philos)
	{
		philos[i].left_f = &data->forks[i];
		philos[i].right_f = &data->forks[i - 1];
	}
	return (SUCCESS);
}

int	init_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	i = -1;
	philos = data->philos;
	while (++i < data->nb_philos)
	{
		philos[i].data = data;
		philos[i].id = i + 1;
		philos[i].nb_meals_had = 0;
		// philos[i].state = IDLE;
		// pthread_mutex_init(&philos[i].mut_state, NULL);
		if (pthread_mutex_init(&philos[i].mut_nb_meals_had, NULL) != 0)
			return (ERROR);
		if (pthread_mutex_init(&philos[i].mut_last_eat_time, NULL) != 0)
			return (ERROR);
		pthread_mutex_lock(&philos[i].mut_last_eat_time);
		philos[i].last_eat_time = get_time();
		pthread_mutex_unlock(&philos[i].mut_last_eat_time);
	}
	return (SUCCESS);
}

int	malloc_data(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->philos)
		return (ERROR);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
		return (free(data->philos), ERROR);
	data->philo_ths = malloc(sizeof(pthread_t) * data->nb_philos);
	if (!data->philo_ths)
		return (free(data->philos), free(data->forks), ERROR);
	return (SUCCESS);
}

int data_init(t_data *data)
{
	if (pthread_mutex_init(&data->mut_eat_t, NULL) != 0)
		return (ERROR);
	if (pthread_mutex_init(&data->mut_sleep_t, NULL) != 0)
		return (ERROR);
	if (pthread_mutex_init(&data->mut_die_t, NULL) != 0)
		return (ERROR);
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (ERROR);
	if (pthread_mutex_init(&data->mut_nb_philos, NULL) != 0)
		return (ERROR);
	if (pthread_mutex_init(&data->mut_keep_iter, NULL) != 0)
		return (ERROR);
	if (pthread_mutex_init(&data->mut_start_time, NULL) != 0)
		return (ERROR);
	return (SUCCESS);
}
int	argument_init(t_data *data, int ac, char **av)
{
	data->nb_full_p = 0;
	data->keep_iterating = true;
	data->nb_philos = ft_atol(av[1]);
	data->die_time = (size_t) ft_atol(av[2]);
	data->eat_time = (size_t) ft_atol(av[3]);
	data->sleep_time = (size_t) ft_atol(av[4]);
	data->nb_meals = -1;
	if (ac == 6)
		data->nb_meals = ft_atol(av[5]);
	if (malloc_data(data) == ERROR)
		return (ERROR);
	if (data_init(data) == ERROR)
		return (ERROR);
	if (init_philos(data) == ERROR)
		return (ERROR);
	if (init_forks(data) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

void	*all_alive_routine(void *data_p)
{
	int		i;
	int		nb_philos;
	t_data	*data;
	t_philo	*philos;

	data = (t_data *)data_p;
	philos = data->philos;
	nb_philos = get_nb_philos(data);
	i = -1;
	while (++i < nb_philos && get_keep_iter(data))
	{
		if (philo_died(&philos[i]) && get_keep_iter(data))
		{
			print_msg(data, philos[i].id, DIED);
			set_keep_iterating(data, false);
			// notify_all_philos(data);
			break ;
		}
		if (i == nb_philos - 1)
			i = -1;
		usleep(1000);
	}
	return (NULL);
}

bool	is_philo_full(t_data *data, t_philo *philo)
{
	bool	result;

	result = false;
	if (get_nb_meals_philo_had(philo) >= data->nb_meals)
		result = true;
	return (result);
}

bool	philo_died(t_philo *philo)
{
	bool		result;
	t_data		*data;

	data = philo->data;
	result = false;
	if (get_time() - get_last_eat_time(philo) > get_die_time(data)
		) // && get_philo_state(philo) != EATING
	{
		// set_philo_state(philo, DEAD);
		result = true;
	}
	return (result);
}

// void	notify_all_philos(t_data *data)
// {
// 	t_philo	*philos;
// 	int		i;
// 	int		nb_philos;

// 	nb_philos = get_nb_philos(data);
// 	philos = data->philos;
// 	i = -1;
// 	while (++i < nb_philos)
// 		philos->
// }

void	*all_full_routine(void *data_p)
{
	t_data	*data;
	int		i;
	int		nb_philos;

	data = (t_data *)data_p;
	i = -1;
	nb_philos = get_nb_philos(data);
	while (++i < nb_philos && get_keep_iter(data))
	{
		usleep(1000);
		if (is_philo_full(data, &data->philos[i]) == false)
			i = -1;
	}
	if (get_keep_iter(data) == true)
	{
		set_keep_iterating(data, false);
		// notify_all_philos(data);
	}
	return (NULL);
}

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

size_t	ft_atol(const char *str)
{
	size_t	i;
	size_t	number;

	i = 0;
	number = 0;
	while (str[i] == ' ' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+')
		i++;
	while ((str[i] >= '0' && str[i] <= '9'))
		number = number * 10 + (str[i++] - '0');
	return (number);
}


bool NonNumericFound(char *s)
{
	if (!s)
		return (true);
	if (*s == '+')
		s++;
	while (*s)
	{
		if (*s <= '9' && *s >= '0')
			s++;
		else
			return (true);
	}
	return (false);
}

int	check_input(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5)
		return (ERROR);
	if (ac > 6)
		return (ERROR);
	while (i < ac)
	{
		if (NonNumericFound(av[i]))
		return (ERROR);
	}
	if (arguments_check(ac, av))
		return (ERROR);
	return (0);
}
int argumentCheckers(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_atol(av[1]) == 0)
			return (printf(RED"at least 2 philos needed to start the sim\n"RESET), ERROR);
		if (ft_atol(av[1]) > 200)
			return (printf("The number of philos should be below 200\n"), ERROR);
		if(NonNumericFound(av[i]))
			return (arguments_error(), ERROR);
		if ((i != 5 && ft_atol(av[i]) == 0))
			return (printf("Please provide a valid input.\n"), ERROR);
		if ((i != 1 && i != 5) && ft_atol(av[i]) < 60)
			return (printf("times Should be above 60ms.\n"));
		i++;
	}
	return (SUCCESS);
}

int	run_threads(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = get_time();
	while (++i < data->nb_philos)
	{
		if (pthread_create(&data->philo_ths[i], NULL,
				&routine, &data->philos[i]))
			return (ERROR);
	}
	if (pthread_create(&data->monitor_th, NULL,
			&all_alive_routine, data))
		return (ERROR);
	if (nb_meals_option(data) == true
		&& pthread_create(&data->monit_all_full, NULL,
			&all_full_routine, data))
		return (ERROR);
	return (SUCCESS);
}

int	join_threads(t_data *data)
{
	int	i;
	int	nb_philos;

	nb_philos = get_nb_philos(data);
	i = -1;
	if (pthread_join(data->monitor_th, NULL) != SUCCESS)
		return (ERROR);
	if (nb_meals_option(data) == true
		&& pthread_join(data->monit_all_full, NULL) != SUCCESS)
		return (ERROR);
	while (++i < nb_philos)
	{
		if (pthread_join(data->philo_ths[i], NULL) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

void	*routine(void *philo_p)
{
	t_philo	*philo;

	philo = (t_philo *) philo_p;
	update_last_meal_time(philo);
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->eat_time - 10);
	while (1)
	{
		if (eat(philo) != 0)
			break ;
		// if (get_philo_state(philo) == DEAD)
		// 	break ;
		if (ft_sleep(philo) != 0)
			break ;
		// if (get_philo_state(philo) == DEAD)
		// 	break ;
		if (think(philo) != 0)
			break ;
	}
	return (NULL);
}

void	print_nb_meals_had(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->print_lock);
	printf("Philo %d ate %d times\n", philo->id, philo->nb_meals_had);
	pthread_mutex_unlock(&data->print_lock);
}

void	set_keep_iterating(t_data *data, bool set_to)
{
	pthread_mutex_lock(&data->mut_keep_iter);
	data->keep_iterating = set_to;
	pthread_mutex_unlock(&data->mut_keep_iter);
}

// void	set_philo_state(t_philo *philo, t_state state)
// {
// 	pthread_mutex_lock(&philo->mut_state);
// 	if (philo->state != DEAD)
// 		philo->state = state;
// 	pthread_mutex_unlock(&philo->mut_state);
// }

int	ft_sleep(t_philo *philo)
{
	// set_philo_state(philo, SLEEPING);
	// if (get_philo_state(philo) == DEAD)
	// 	return (1);
	print_msg(philo->data, philo->id, SLEEP);
	ft_usleep(get_sleep_time(philo->data));
	return (0);
}

int	think(t_philo *philo)
{
	// set_philo_state(philo, THINKING);
	// if (get_philo_state(philo) == DEAD)
		// return (1);
	print_msg(philo->data, philo->id, THINK);
	return (0);
}

void	wait_until(size_t wakeup_time)
{
	int			margin;
	size_t	time;

	margin = 5;
	while (1)
	{
		time = get_time();
		if (wakeup_time <= time + margin)
		{
			while (wakeup_time > time)
				time = get_time();
			break ;
		}
		else
		{
			usleep(1000 * (wakeup_time - time - margin));
		}
	}
}

void	ft_usleep(size_t sleep_time)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < sleep_time)
		usleep(500);
}

size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (size_t)1000) + (tv.tv_usec / 1000));
}

int	handle_1_philo(t_philo *philo)
{
	take_left_fork(philo);
	ft_usleep(get_die_time(philo->data));
	// set_philo_state(philo, DEAD);
	return (1);
}

bool	nb_meals_option(t_data *data)
{
	if (data->nb_meals > 0)
		return (true);
	return (false);
}

void	free_data(t_data *data)
{
	int	i;
	int	nb_philos;

	nb_philos = get_nb_philos(data);
	i = -1;
	while (++i < nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		// pthread_mutex_destroy(&data->philos[i].mut_state);
		pthread_mutex_destroy(&data->philos[i].mut_nb_meals_had);
		pthread_mutex_destroy(&data->philos[i].mut_last_eat_time);
	}
	pthread_mutex_destroy(&data->mut_die_t);
	pthread_mutex_destroy(&data->mut_eat_t);
	pthread_mutex_destroy(&data->mut_sleep_t);
	pthread_mutex_destroy(&data->mut_nb_philos);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->mut_keep_iter);
	pthread_mutex_destroy(&data->mut_start_time);
	free(data->philo_ths);
	free(data->philos);
	free(data->forks);
}

void	print_msg(t_data *data, int id, char *msg)
{
	size_t	time;

	time = get_time() - get_start_time(data);
	pthread_mutex_lock(&data->print_lock);
	if (get_keep_iter(data))
		printf("%lu %d %s\n", time, id, msg);
	pthread_mutex_unlock(&data->print_lock);
}

void	print_mut(t_data *data, char *msg)
{
	pthread_mutex_lock(&data->print_lock);
	printf("%s\n", msg);
	pthread_mutex_unlock(&data->print_lock);
}


int	main(int ac, char **av)
{
	t_data	data;

	if (argumentCheckers(av)!= SUCCESS)
		return (arguments_error(), ERROR);
	if (argument_init(&data, ac, av) != SUCCESS)
		return (ERROR);
	if (run_threads(&data) != SUCCESS)
		return (ERROR);
	if (join_threads(&data) != SUCCESS)
		return (ERROR);
	free_data(&data);

	return (SUCCESS);
}