/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:59:19 by seemil            #+#    #+#             */
/*   Updated: 2024/10/27 16:59:22 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	*init_create_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t) * table->number_of_philosophers);
	if (!forks)
		return (exit_error_null(MALLOC_ERROR, NULL, 0));
	i = 0;
	while (i < table->number_of_philosophers)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (exit_error_null(MUTEX_ERROR, NULL, 0));
		i++;
	}
	return (forks);
}

static bool	init_mutexes(t_table *table)
{
	table->fork_locks = init_create_forks(table);
	if (!table->fork_locks)
		return (false);
	if (pthread_mutex_init(&table->simulation_stop_lock, 0) != 0)
		return (exit_error_failure(MUTEX_ERROR, NULL, table));
	if (pthread_mutex_init(&table->write_lock, 0) != 0)
		return (exit_error_failure(MUTEX_ERROR, NULL, table));
	return (true);
}

static void	init_assign_forks(t_philo *philo)
{
	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->table->number_of_philosophers;
	if (philo->id == philo->table->number_of_philosophers - 1)
	{
		philo->fork[0] = 0;
		philo->fork[1] = philo->id;
	}
}

static t_philo	**init_philosophers(t_table *table)
{
	t_philo			**philos;
	unsigned int	i;

	philos = malloc(sizeof(t_philo) * table->number_of_philosophers);
	if (!philos)
		return (exit_error_null(MALLOC_ERROR, NULL, 0));
	i = 0;
	while (i < table->number_of_philosophers)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		if (!philos[i])
			return (exit_error_null(MALLOC_ERROR, NULL, 0));
		if (pthread_mutex_init(&philos[i]->meal_lock, 0) != 0)
			return (exit_error_null(MUTEX_ERROR, NULL, 0));
		philos[i]->table = table;
		philos[i]->last_meal = 0;
		philos[i]->id = i;
		philos[i]->meals_eaten = 0;
		init_assign_forks(philos[i]);
		i++;
	}
	return (philos);
}

t_table	*table_init(int argc, char **argv, int i)
{
	t_table	*table;

	table = malloc(sizeof(t_table) * 1);
	if (!table)
		return (exit_error_null(MALLOC_ERROR, NULL, 0));
	table->number_of_philosophers = check_int_atoi(argv[i++]);
	table->time_to_die = check_int_atoi(argv[i++]);
	table->time_to_eat = check_int_atoi(argv[i++]);
	table->time_to_sleep = check_int_atoi(argv[i++]);
	table->num_times_to_eat = -1;
	if (argc - 1 == 5)
		table->num_times_to_eat = check_int_atoi(argv[i]);
	table->philos = init_philosophers(table);
	if (!table->philos)
		return (NULL);
	if (!init_mutexes(table))
		return (NULL);
	table->simulation_stop = false;
	return (table);
}
