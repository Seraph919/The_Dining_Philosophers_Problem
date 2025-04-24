/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:14:43 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/24 17:52:13 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_message(t_philo *philo, char *msg)
{
	size_t	time;
	bool	not_full;

	not_full = philo->meal_counter < philo->max_meals;
	sem_wait(philo->data->print_lock);
	time = ms_curr_time() - philo->data->start_time;
	if (philo->data->stop->__align != 1 && philo->dead == false)
	{
		if (philo->id % 2)
			printf(BLUE "%zu %zu %s\n" RESET, time, philo->id, msg);
		else
			printf(GREEN "%zu %zu %s\n" RESET, time, philo->id, msg);
	}
	else if (msg[0] == 'd' && philo->data->print_bool->__align != 0 && (not_full
			|| philo->max_meals == -1))
	{
		sem_wait(philo->data->bool_lock);
		philo->data->print_bool->__align = 0;
		sem_post(philo->data->bool_lock);
		printf(RED "%zu %zu %s\n" RESET, time, philo->id, DIED);
		sem_post(philo->data->print_lock);
		philo->data->stop->__align = 1;
		return ;
	}
	sem_post(philo->data->print_lock);
}

void	fork_taking(t_philo *philo)
{
	if (philo->id % 2)
		usleep(200);
	if (philo->data->number_of_philos < 100)
		usleep(500);
	sem_wait(philo->data->forks);
	print_message(philo, FORK);
	sem_wait(philo->data->forks);
	print_message(philo, FORK);
}

int	eating(t_philo *philo)
{
	fork_taking(philo);
	print_message(philo, EAT);
	mssleep(philo->data->time_to_eat, philo, false);
	pthread_mutex_lock(&philo->last_meal_up);
	philo->last_meal_t = ms_curr_time();
	pthread_mutex_unlock(&philo->last_meal_up);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meal_counter++;
	if (philo->meal_counter >= philo->max_meals && philo->max_meals != -1)
		return (post_and_end(philo), ERROR);
	pthread_mutex_unlock(&philo->meal_mutex);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	pthread_mutex_lock(&philo->dead_lock);
	if (philo->dead == true && philo->meal_counter != philo->max_meals)
	{
		philo->data->stop->__align = 1;
		pthread_mutex_unlock(&philo->dead_lock);
		return (ERROR);
	}
	pthread_mutex_unlock(&philo->dead_lock);
	return (SUCCESS);
}

int	thinking(t_philo *philo)
{
	print_message(philo, TNK);
	return (SUCCESS);
}

int	sleeping(t_philo *philo)
{
	mssleep(philo->data->time_to_sleep, philo, false);
	print_message(philo, SLEEP);
	return (SUCCESS);
}
