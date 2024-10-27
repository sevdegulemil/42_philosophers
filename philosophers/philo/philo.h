/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:24:06 by seemil            #+#    #+#             */
/*   Updated: 2024/10/06 16:57:26 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>

# define ERROR "!error!\n"
# define USAGE_ERROR "%sUsage should be: ./philo (number_of_philosophers) \
(time_to_die) (time_to_eat) (time_to_sleep) \
[number_of_times_each_philosopher_must_eat]\n"
# define INPUT_ERROR	"%s invalid input\n"
# define SYNTX_ERR "!syntax error!"
# define MALLOC_ERROR	"%s error: could not allocate memory.\n"
# define MUTEX_ERROR	"%s error: could not create mutex.\n"
# define THREAD_ERROR	"%s error: could not create thread.\n"

# define MAX_PHILOS	200
# define STR_MAX_PHILOS "200"

# ifndef DEBUG_FORMATTING
#  define DEBUG_FORMATTING 0
# endif

typedef struct s_philo	t_philo;

typedef enum e_status
{
	DIED,
	EATING,
	SLEEPING,
	THINKING,
	GRABBED_FORK_1,
	GRABBED_FORK_2
}	t_status;

typedef struct s_table
{
	unsigned int	number_of_philosophers;
	int				num_times_to_eat;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			start_time;
	bool			simulation_stop;
	pthread_mutex_t	simulation_stop_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*fork_locks;
	pthread_t		exit_death;
	t_philo			**philos;
}	t_table;

typedef struct s_philo
{
	pthread_t			thread;
	unsigned int		id;
	unsigned int		meals_eaten;
	time_t				last_meal;
	pthread_mutex_t		meal_lock;
	unsigned int		fork[2];
	t_table				*table;
}	t_philo;

/*about_time.c*/
void	philo_usleep_until_complete(t_table *table, time_t sleep_time);
void	wait_until_start_time(time_t start_time);
time_t	get_time_in_ms(void);

/*death.c*/
void	*exit_death(void *data);
bool	exit_has_sim_stopped(t_table *table);

/*exit.c*/
void	exit_destroy_mutexes(t_table *table);
int		exit_error_failure(char *str, char *details, t_table *table);
void	*exit_free_table(t_table *table);
void	*exit_error_null(char *str, char *details, t_table *table);
int		exit_msg(char *str, char *detail, int exit_no);

/*init.c*/
t_table	*table_init(int argc, char **argv, int i);

/*is_input_valid.c*/
int		check_int_atoi(char *str);
bool	check_input_valid(int argc, char **argv);

/*output.c*/
void	output_outcome(t_table *table);
void	output_status_debug(t_philo *philo, t_status status);
void	print_output_status(t_philo *philo, bool reaper_report, \
		t_status status);

/*philosopher.c*/
void	*philosopher(void *data);

#endif
