/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:15:46 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/21 17:20:55 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <unistd.h>
# include "../printfd/printfd.h"

# define RESET "\033[0m"
# define BLUE "\033[1;34m"
# define GREEN "\033[1;32m"
# define RED "\033[1;31m"
# define SUCCESS 0
# define ERROR 1
# define SLEEP "is sleeping"
# define EAT "is eating"
# define TNK "is thinking"
# define FORK "has taken a fork"
# define DIED "died"

typedef struct s_data	t_data;

typedef struct s_philo
{
	t_data				*data;
	pthread_mutex_t		m_lock;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		last_meal_up;
	int					meal_counter;
	int					max_meals;
	size_t				last_meal_t;
	bool				dead;
	size_t				id;
}						t_philo;

typedef struct t_garbage
{
	void				*allocated;
	struct t_garbage	*next;
}						t_garbage;

typedef struct s_data
{
	sem_t				*forks;
	sem_t				*print_lock;
	sem_t				*quiter;
	sem_t				*all_full;
	t_philo				*philos;
	sem_t				*fork_lock;
	int					*ids;
	t_garbage			**garbage;
	size_t				start_time;
	size_t				meal_counter;
	size_t				number_of_philos;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				last_mealtime;
	int					must_eat_number;
	bool				should_start;
	bool				philo_died;
	bool				ender;
}						t_data;

int						simulation(t_data *data);
int						arguments_error(void);
int						argument_checkers(char **av);
int						av_arguments_init(t_data *data, char **av);
int						data_init(t_data *data, char **av);
size_t					ms_curr_time(void);
void					mssleep(size_t milliseconds);
void					exit_message(char *s, int status);
bool					non_num_found(char *s);
unsigned long			ft_atol(const char *str);
void					eating(t_philo *philo);
void					thinking(t_philo *philo);
void					sleeping(t_philo *philo);
void					print_message(t_philo *philo, char *msg);
void					fireforce(t_data *data);
void					waitformeals(t_data *data, int i);
void					waitfor_death(t_data *data, int i);
bool					risky(t_data *data);
void					post_and_end(t_philo *philo);
void					fireforce(t_data *data);

#endif