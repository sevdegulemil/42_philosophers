/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_input_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:59:26 by seemil            #+#    #+#             */
/*   Updated: 2024/10/27 16:59:28 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

int	check_int_atoi(char *str)
{
	unsigned long long int	num;
	int						i;

	i = 0;
	num = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (num > INT_MAX)
		return (-1);
	return ((int)num);
}

bool	check_input_valid(int argc, char **argv)
{
	int	i;
	int	num;

	i = 1;
	while (i < argc)
	{
		if (!check_only_digits(argv[i]))
			return (exit_msg(INPUT_ERROR, argv[i], false));
		num = check_int_atoi(argv[i]);
		if (i == 1 && (num <= 0 || num > MAX_PHILOS))
			return (exit_msg(INPUT_ERROR, STR_MAX_PHILOS, false));
		if (i != 1 && num == -1)
			return (exit_msg(INPUT_ERROR, argv[i], false));
		i++;
	}
	return (true);
}
