/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:59:13 by seemil            #+#    #+#             */
/*   Updated: 2024/10/27 16:59:15 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_destroy_mutexes(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		pthread_mutex_destroy(&table->fork_locks[i]);
		pthread_mutex_destroy(&table->philos[i]->meal_lock);
		i++;
	}
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->simulation_stop_lock);
}

int	exit_error_failure(char *str, char *details, t_table *table)
{
	if (table != NULL)
		exit_free_table(table);
	return (exit_msg(str, details, 0));
}

void	*exit_free_table(t_table *table)
{
	unsigned int	i;

	if (!table)
		return (NULL);
	if (table->fork_locks != NULL)
		free(table->fork_locks);
	if (table->philos != NULL)
	{
		i = 0;
		while (i < table->number_of_philosophers)
		{
			if (table->philos[i] != NULL)
				free(table->philos[i]);
			i++;
		}
		free(table->philos);
	}
	free(table);
	return (NULL);
}

void	*exit_error_null(char *str, char *details, t_table *table)
{
	if (table != NULL)
		exit_free_table(table);
	exit_msg(str, details, EXIT_FAILURE);
	return (NULL);
}

int	exit_msg(char *str, char *detail, int exit_no)
{
	if (!detail)
		printf(str, ERROR);
	else
		printf(str, ERROR, detail);
	return (exit_no);
}
