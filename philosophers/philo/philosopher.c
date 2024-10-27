/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:59:53 by seemil            #+#    #+#             */
/*   Updated: 2024/10/27 16:59:55 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eat_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	print_output_status(philo, false, GRABBED_FORK_1);
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[1]]);
	print_output_status(philo, false, GRABBED_FORK_2);
	print_output_status(philo, false, EATING);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_lock);
	philo_usleep_until_complete(philo->table, philo->table->time_to_eat);
	if (exit_has_sim_stopped(philo->table) == false)
	{
		pthread_mutex_lock(&philo->meal_lock);
		philo->meals_eaten += 1;
		pthread_mutex_unlock(&philo->meal_lock);
	}
	print_output_status(philo, false, SLEEPING);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
	philo_usleep_until_complete(philo->table, philo->table->time_to_sleep);
}

static void	philo_think(t_philo *philo, bool silent)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_lock);
	time_to_think = (philo->table->time_to_die
			- (get_time_in_ms() - philo->last_meal)
			- philo->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == true)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (silent == false)
		print_output_status(philo, false, THINKING);
	philo_usleep_until_complete(philo->table, time_to_think);
}

static void	*philo_single_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	print_output_status(philo, false, GRABBED_FORK_1);
	philo_usleep_until_complete(philo->table, philo->table->time_to_die);
	print_output_status(philo, false, DIED);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
	return (NULL);
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->table->num_times_to_eat == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->meal_lock);
	wait_until_start_time(philo->table->start_time);
	if (philo->table->time_to_die == 0)
		return (NULL);
	if (philo->table->number_of_philosophers == 1)
		return (philo_single_routine(philo));
	else if (philo->id % 2)
		philo_think(philo, true);
	while (exit_has_sim_stopped(philo->table) == false)
	{
		philo_eat_sleep(philo);
		philo_think(philo, false);
	}
	return (NULL);
}
