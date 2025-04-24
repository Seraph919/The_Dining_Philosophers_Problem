/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:21:37 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/22 12:04:55 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include "../printfd/printfd.h"

# define ERROR 1
# define SUCCESS 0

# define RESET "\033[0m"
# define MAGEN "\033[48;5;2m"
# define BLUE "\033[1;34m"
# define GREEN "\033[1;32m"
# define RED "\033[1;31m"
# define GOUZ "\033[38;5;198m"

# define TAKE_FORKS "has taken a fork"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define EAT "is eating"
# define DIED "died"

typedef enum e_philo_state
{
	EATING = 0,
	SLEEPING = 1,
	THINKING = 2,
	DEAD = 3,
	FULL = 4,
	IDLE = 5
}					t_state;

typedef struct s_philo
{
	int				id;
	int				nb_meals_had;
	struct s_data	*data;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	pthread_mutex_t	last_eat_mutex;
	size_t			last_eat_time;
}					t_philo;

typedef struct s_data
{
	int				philo_nbrs;
	int				meal_nbr;
	int				max_nmeals;
	bool			no_one_died;
	size_t			start_time;
	size_t			time2eat;
	size_t			time2sleep;
	size_t			time2die;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	meal_counter_mutex;
	pthread_mutex_t	phile_died_mutex;

	pthread_mutex_t	print_lock;
	pthread_mutex_t	non_dead_mutex;
	pthread_t		monitor_th;
	pthread_t		monit_all_full;
	pthread_t		*philo_ths;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}					t_data;

int					eating(t_philo *philo);
int					take_left_fork(t_philo *philo);
int					take_right_fork(t_philo *philo);
int					take_forks(t_philo *philo);
int					forks_init(t_data *data);
int					philo_init(t_data *data);
int					arguments_error(void);
void				*monitor(void *data_p);
bool				philo_died(t_philo *philo);
int					arguments_check(int argc, char **argv);
long long			ft_atol(const char *str);
int					check_input(int argc, char **argv);
int					simulation(t_data *data);
void				*routine(void *philo_p);
int					sleeping(t_philo *philo);
int					thinking(t_philo *philo);
void				mssleep(size_t sleep_time, t_data *data);
size_t				ms_curr_time(void);
void				handle_1_philo(t_philo *philo);
void				fireforce(t_data *data);
void				print_msg(t_data *data, int id, char *msg);
int					argument_checkers(char **av);
int					initialization(t_data *data, char **av);
int					mutex_inits(t_data *data);
bool				non_numeric_found(char *s);
int					return_error(char *msg);

#endif
