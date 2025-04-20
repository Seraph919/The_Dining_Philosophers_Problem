/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:14:43 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/20 19:56:59 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
	the monitor function is used to check if the philosopher has died
	I'ts running in a separate thread and it checks if the last meal time
	is greater than the time to die
	if it is, then we set the dead flag to true and post to the quiter semaphore
	which will cause the main process to kill all the philosophers and exit.

	i faced several issues with the monitor function, especially
	with the data races.
	so I had to use a mutex lock to protect the access to the last meal time
	and the dead flag.
	also..
	it was previously like this :

	void *monitor(void *arg)
	{
		t_philo *philo;

		philo = (t_philo *)arg;
		while (1)
		{
			pthread_mutex_lock(&philo->m_lock);
			if (philo->last_meal_t > 0)
			{
				if (philo->data->time_to_die <= msCrntTime()-philo->last_meal_t)
				{
					pthread_mutex_lock(&philo->dead_lock);
					philo->dead = true;
					pthread_mutex_unlock(&philo->dead_lock);
					sem_post(philo->data->quiter);
					pthread_mutex_unlock(&philo->m_lock); // Ensure unlock
					break;
				}
			}
			pthread_mutex_unlock(&philo->m_lock); // Ensure unlock in other cases
		}
		return (NULL);
	}
	but it exists before unlocking the mutex lock (m_lock), which
	caused a deadlock.
	so I had to use a boolean flag to check if
	the monitor function should exit or not.
*/

/*
	had to add a delay some philos to avoid the deadlocks
*/

void	print_message(t_philo *philo, char *msg)
{
	size_t	time;
	bool	not_full;

	not_full = philo->meal_counter < philo->max_meals;
	sem_wait(philo->data->print_lock);
	time = msCrntTime() - philo->data->start_time;
	if (philo->dead == false)
	{
		if (philo->id % 2)
			printf(BLUE"%zu %zu is %s\n"RESET, time, philo->id, msg);
		else
			printf(GREEN"%zu %zu is %s\n"RESET, time, philo->id, msg);
	}
	else if (msg[0] == 'd' && (not_full || philo->max_meals == -1))
	{
		printf(RED "%zu %zu %s\n" RESET, time, philo->id, DIED);
		sem_post(philo->data->print_lock);
		sem_post(philo->data->quiter);
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

void	eating(t_philo *philo)
{
	fork_taking(philo);
	pthread_mutex_lock(&philo->last_meal_up);
	philo->last_meal_t = msCrntTime();
	pthread_mutex_unlock(&philo->last_meal_up);
	print_message(philo, EAT);
	mssleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->m_lock);
	philo->meal_counter++;
	if (philo->meal_counter == philo->max_meals)
		return (post_and_end(philo));
	pthread_mutex_unlock(&philo->m_lock);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	pthread_mutex_lock(&philo->dead_lock);
	if (philo->dead == true && philo->meal_counter != philo->max_meals)
		sem_post(philo->data->quiter);
	pthread_mutex_unlock(&philo->dead_lock);
}

void	thinking(t_philo *philo)
{
	print_message(philo, TNK);
}

void	sleeping(t_philo *philo)
{
	print_message(philo, SLEEP);
	mssleep(philo->data->time_to_sleep);
}
