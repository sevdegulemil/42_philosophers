/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:59:34 by seemil            #+#    #+#             */
/*   Updated: 2024/10/27 16:59:36 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	simulation_stop(t_table	*table)
{
	unsigned int	i;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		pthread_join(table->philos[i]->thread, NULL);
		i++;
	}
	if (table->number_of_philosophers > 1)
		pthread_join(table->exit_death, NULL);
	if (DEBUG_FORMATTING == true && table->num_times_to_eat != -1)
		output_outcome(table);
	exit_destroy_mutexes(table);
	exit_free_table(table);
}

static bool	simulation_start(t_table *table)
{
	unsigned int	i;

	table->start_time = (get_time_in_ms()) + \
						(table->number_of_philosophers * 2 * 10);
	i = 0;
	while (i < table->number_of_philosophers)
	{
		if (pthread_create(&table->philos[i]->thread, NULL,
				&philosopher, table->philos[i]) != 0)
			return (exit_error_failure(THREAD_ERROR, NULL, table));
		i++;
	}
	if (table->number_of_philosophers > 1)
	{
		if (pthread_create(&table->exit_death, NULL,
				&exit_death, table) != 0)
			return (exit_error_failure(THREAD_ERROR, NULL, table));
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if (argc - 1 < 4 || argc - 1 > 5)
		return (exit_msg(USAGE_ERROR, NULL, EXIT_FAILURE));
	if (!check_input_valid(argc, argv))
		return (EXIT_FAILURE);
	table = table_init(argc, argv, 1);
	if (!table)
		return (EXIT_FAILURE);
	if (!simulation_start(table))
		return (EXIT_FAILURE);
	simulation_stop(table);
	return (EXIT_SUCCESS);
}
