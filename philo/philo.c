/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:25:10 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/18 12:11:16 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (philo_died(philo))
		return (1);
	pthread_mutex_lock(philo->left_f);
	print_msg(philo->data, philo->id, TAKE_FORKS);
	return (0);
}

int	take_right_fork(t_philo *philo)
{
	if (philo_died(philo))
		return (1);
	pthread_mutex_lock(philo->right_f);
	print_msg(philo->data, philo->id, TAKE_FORKS);
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (take_left_fork(philo) != 0 || philo_died(philo))
			return (1);
		if (take_right_fork(philo) != 0|| philo_died(philo))
		{
			pthread_mutex_unlock(philo->left_f);
			return (1);
		}
	}
	else
	{
		if (take_right_fork(philo) != 0 || philo_died(philo))
			return (1);
		if (take_left_fork(philo) != 0 || philo_died(philo))
		{
			pthread_mutex_unlock(philo->right_f);
			return (1);
		}
	}
	return (0);
}

bool	is_philo_full(t_data *data, t_philo *philo)
{
	bool	result;

	result = false;
	if (philo->nb_meals_had >= data->max_nmeals)
		result = true;
	return (result);
}

bool	philo_died(t_philo *philo)
{
	t_data		*data;

	data = philo->data;
	pthread_mutex_lock(&data->die_mutex);
	if (get_time() - philo->last_eat_time > data->time2die )
	{
		printf(RED"DIED\n"RESET);
		pthread_mutex_unlock(&data->die_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->die_mutex);
	return (false);
}

int	thread_creation(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = get_time();
	while (++i < data->philo_nbrs)
	{
		if (pthread_create(&data->philo_ths[i], NULL,
				&routine, &data->philos[i]))
			return (ERROR);
	}
	if (pthread_create(&data->monitor_th, NULL,
			&all_alive_routine, data))
		return (ERROR);
	// if (data->nb_meals != -1
	// 	&& pthread_create(&data->monit_all_full, NULL,
	// 		&all_full_routine, data))
	// 	return (ERROR);
	return (SUCCESS);
}

int	join_threads(t_data *data)
{
	int	i;

	i = -1;
	if (pthread_join(data->monitor_th, NULL) != SUCCESS)
		return (ERROR);
	while (++i < data->philo_nbrs)
	{
		if (pthread_join(data->philo_ths[i], NULL) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}


void	print_nb_meals_had(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->print_lock);
	printf("Philo %d ate %d times\n", philo->id, philo->nb_meals_had);
	pthread_mutex_unlock(&data->print_lock);
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

void	handle_1_philo(t_philo *philo)
{
	take_left_fork(philo);
	usleepp(philo->data->time2die);
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_lock(&philo->data->mut_keep_iter);
	philo->data->no_one_died = false;
	pthread_mutex_unlock(&philo->data->mut_keep_iter);
}

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbrs)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].mut_nb_meals_had);
		pthread_mutex_destroy(&data->philos[i].mut_last_eat_time);
	}
	pthread_mutex_destroy(&data->die_mutex);
	pthread_mutex_destroy(&data->eat_mutex);
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

	time = get_time() - data->start_time;
	pthread_mutex_lock(&data->print_lock);
	pthread_mutex_lock(&data->mut_keep_iter);
	if (data->no_one_died)
	{
		pthread_mutex_unlock(&data->mut_keep_iter);
		if (id % 2)
		printf(BLUE"%lu %d %s\n"RESET, time, id, msg);
		else
		printf(GREEN"%lu %d %s\n"RESET, time, id, msg);
	}
	pthread_mutex_unlock(&data->print_lock);
}

void	print_mut(t_data *data, char *msg)
{
	pthread_mutex_lock(&data->print_lock);
	printf("%s\n", msg);
	pthread_mutex_unlock(&data->print_lock);
}
