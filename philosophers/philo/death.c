/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:59:01 by seemil            #+#    #+#             */
/*   Updated: 2024/10/27 16:59:04 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	exit_stop_flag(t_table *table, bool state)
{
	pthread_mutex_lock(&table->simulation_stop_lock);
	table->simulation_stop = state;
	pthread_mutex_unlock(&table->simulation_stop_lock);
}

static bool	exit_kill_philo(t_philo *philo)
{
	time_t	time;

	time = get_time_in_ms();
	if ((time - philo->last_meal) >= philo->table->time_to_die)
	{
		exit_stop_flag(philo->table, true);
		print_output_status(philo, true, DIED);
		pthread_mutex_unlock(&philo->meal_lock);
		return (true);
	}
	return (false);
}

static bool	exit_end_condition(t_table *table)
{
	unsigned int	i;
	bool			everyone_ate_enough;

	everyone_ate_enough = true;
	i = 0;
	while (i < table->number_of_philosophers)
	{
		pthread_mutex_lock(&table->philos[i]->meal_lock);
		if (exit_kill_philo(table->philos[i]))
			return (true);
		if (table->num_times_to_eat != -1)
			if (table->philos[i]->meals_eaten
				< (unsigned int)table->num_times_to_eat)
				everyone_ate_enough = false;
		pthread_mutex_unlock(&table->philos[i]->meal_lock);
		i++;
	}
	if (table->num_times_to_eat != -1 && everyone_ate_enough == true)
	{
		exit_stop_flag(table, true);
		return (true);
	}
	return (false);
}

void	*exit_death(void *data)
{
	t_table			*table;

	table = (t_table *)data;
	if (table->num_times_to_eat == 0)
		return (NULL);
	exit_stop_flag(table, false);
	wait_until_start_time(table->start_time);
	while (true)
	{
		if (exit_end_condition(table) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

bool	exit_has_sim_stopped(t_table *table)
{
	bool	is_stopped;

	is_stopped = false;
	pthread_mutex_lock(&table->simulation_stop_lock);
	if (table->simulation_stop == true)
		is_stopped = true;
	pthread_mutex_unlock(&table->simulation_stop_lock);
	return (is_stopped);
}
