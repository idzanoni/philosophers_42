/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:38:46 by izanoni           #+#    #+#             */
/*   Updated: 2024/10/18 18:46:24 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(int argc, char **argv)
{
	if (number_of_args(argc) != 0)
		return (1);
	if (args_is_num(argv) != 0)
		return (1);
	if (max_min_philo(argv) != 0)
		return (1);
	if (min_time(argv) != 0)
		return (1);
	return (0);
}

int	number_of_args(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Wrong Input!\n");
		return (1);
	}
	return (0);
}

int	args_is_num(char **argv)
{
	int	count;
	int	i;

	i = 1;
	count = 0;
	while (argv[i] != NULL)
	{
		count = 0;
		while (argv[i][count] != '\0')
		{
			if (philo_isalpha(argv[i][count]) == 1)
			{
				printf("Invalid arguments\n");
				return (1);
			}
			count++;
		}
		i++;
	}
	return (0);
}

int	max_min_philo(char	**argv)
{
	int	philo_number;

	philo_number = philo_atoi(argv[1]);
	if (philo_number > 200 || philo_number < 1)
	{
		printf("Invalid arguments\n");
		return (1);
	}
	else
		return (0);
}

int	min_time(char **argv)
{
	int	i;

	i = 2;
	while (i < 5)
	{
		if (philo_atoi(argv[i]) < 60)
		{
			printf("Invalid arguments\n");
			return (1);
		}
		i++;
	}
	return (0);
}
