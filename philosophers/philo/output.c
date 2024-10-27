/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:59:42 by seemil            #+#    #+#             */
/*   Updated: 2024/10/27 16:59:44 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	output_outcome(t_table *table)
{
	unsigned int	i;
	unsigned int	full_count;

	full_count = 0;
	i = 0;
	while (i < table->number_of_philosophers)
	{
		if (table->philos[i]->meals_eaten
			>= (unsigned int)table->num_times_to_eat)
			full_count++;
		i++;
	}
	pthread_mutex_lock(&table->write_lock);
	printf("%d/%d philosophers had at least %d meals.\n",
		full_count, table->number_of_philosophers, table->num_times_to_eat);
	pthread_mutex_unlock(&table->write_lock);
	return ;
}

static void	output_print_status(t_philo *philo, char *str)
{
	printf("%ld %d %s\n", get_time_in_ms() - philo->table->start_time,
		philo->id + 1, str);
}

static void	output_print_status_debug(t_philo *philo, \
		char *str, t_status status) //incele
{
	if (status == GRABBED_FORK_1)
		printf("[%10ld]\t%03d\t%s: fork [%d]\n",
			get_time_in_ms() - philo->table->start_time,
			philo->id + 1, str, philo->fork[0]);
	else if (status == GRABBED_FORK_2)
		printf("[%10ld]\t%03d\t%s: fork [%d]\n",
			get_time_in_ms() - philo->table->start_time,
			philo->id + 1, str, philo->fork[1]);
	else
		printf("[%10ld]\t%03d\t%s\n",
			get_time_in_ms() - philo->table->start_time,
			philo->id + 1, str);
}

void	output_status_debug(t_philo *philo, t_status status)
{
	if (status == DIED)
		output_print_status_debug(philo, "died", status);
	else if (status == EATING)
		output_print_status_debug(philo, "is eating", status);
	else if (status == SLEEPING)
		output_print_status_debug(philo, "is sleeping", status);
	else if (status == THINKING)
		output_print_status_debug(philo, "is thinking", status);
	else if (status == GRABBED_FORK_1)
		output_print_status_debug(philo, "has taken a fork", status);
	else if (status == GRABBED_FORK_2)
		output_print_status_debug(philo, "has taken a fork", status);
}

void	print_output_status(t_philo *philo, bool reaper_report, t_status status)
{
	pthread_mutex_lock(&philo->table->write_lock);
	if (exit_has_sim_stopped(philo->table) == true && reaper_report == false)
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		return ;
	}
	if (DEBUG_FORMATTING == true)
	{
		output_status_debug(philo, status);
		pthread_mutex_unlock(&philo->table->write_lock);
		return ;
	}
	if (status == DIED)
		output_print_status(philo, "died");
	else if (status == EATING)
		output_print_status(philo, "is eating");
	else if (status == SLEEPING)
		output_print_status(philo, "is sleeping");
	else if (status == THINKING)
		output_print_status(philo, "is thinking");
	else if (status == GRABBED_FORK_1 || status == GRABBED_FORK_2)
		output_print_status(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->table->write_lock);
}
