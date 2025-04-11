/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:21:37 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/11 14:50:12 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <stdbool.h>

# define ERROR 1
# define SUCCESS 0

# define RESET   "\033[0m"
# define MAGEN "\033[48;5;2m"
# define BLUE  "\033[1;34m"
# define GREEN  "\033[1;32m"
# define RED	"\033[1;31m"
# define GOUZ	"\033[38;5;198m"

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
}	t_state;


typedef struct s_philo
{
	int				id;
	int				nb_meals_had;
	struct s_data	*data;
	// t_state			state;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	// pthread_mutex_t	mut_state;
	pthread_mutex_t	mut_nb_meals_had;
	pthread_mutex_t	mut_last_eat_time;
	size_t		last_eat_time;
}				t_philo;



typedef struct s_data
{
	int				nb_philos;
	int				nb_meals;
	int				nb_full_p;
	bool			keep_iterating;
	size_t		eat_time;
	size_t		die_time;
	size_t		sleep_time;
	size_t		start_time;
	pthread_mutex_t	mut_eat_t;
	pthread_mutex_t	mut_die_t;
	pthread_mutex_t	mut_sleep_t;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	mut_nb_philos;
	pthread_mutex_t	mut_keep_iter;
	pthread_mutex_t	mut_start_time;
	pthread_t		monitor_th;
	pthread_t		monit_all_full;
	pthread_t		*philo_ths;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}				t_data;

void	unlock(t_philo *philo);
void	update_last_meal_time(t_philo *philo);
void	update_nb_meals_had(t_philo *philo);
void	sleep_for_eating(t_philo *philo);
int	eat(t_philo *philo);
void	drop_left_fork(t_philo *philo);
void	drop_right_fork(t_philo *philo);
int	take_left_fork(t_philo *philo);
int	take_right_fork(t_philo *philo);
int	take_forks(t_philo *philo);
bool	get_keep_iter(t_data *data);
int	get_nb_philos(t_data *data);
int	get_nb_meals_philo_had(t_philo *philo);
size_t	get_start_time(t_data *data);
size_t	get_die_time(t_data *data);
size_t	get_sleep_time(t_data *data);
size_t	get_eat_time(t_data *data);
size_t	get_last_eat_time(t_philo *philo);
int	init_forks(t_data *data);
int	init_philos(t_data *data);
int	malloc_data(t_data *data);
int	arguments_error(void);
void	*all_alive_routine(void *data_p);
bool	is_philo_full(t_data *data, t_philo *philo);
bool	philo_died(t_philo *philo);
void	notify_all_philos(t_data *data);
void	*all_full_routine(void *data_p);
void	print_instruction(void);
int	arguments_check(int argc, char **argv);
size_t	ft_atol(const char *str);
int	is_input_digit(int argc, char **argv);
int	check_input(int argc, char **argv);
int	run_threads(t_data *data);
int	join_threads(t_data *data);
void	leaks(void);
int	main(int argc, char **argv);
void	*routine(void *philo_p);
void	print_nb_meals_had(t_philo *philo);
void	set_keep_iterating(t_data *data, bool set_to);
int	ft_sleep(t_philo *philo);
int	think(t_philo *philo);
void	wait_until(size_t wakeup_time);
void	ft_usleep(size_t sleep_time);
size_t	get_time(void);
int	handle_1_philo(t_philo *philo);
bool	nb_meals_option(t_data *data);
void	free_data(t_data *data);
void	print_msg(t_data *data, int id, char *msg);
void	print_mut(t_data *data, char *msg);

#endif
