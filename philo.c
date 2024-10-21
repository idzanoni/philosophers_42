/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:02:51 by izanoni           #+#    #+#             */
/*   Updated: 2024/10/18 18:46:27 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	ph_data;
	t_philo	*thinker;

	if (check_input(argc, argv) == 1)
		return (-1);
	else
	{
		ph_data = init_data(argc, argv);
		thinker = init_philo(&ph_data);
	}	
	return (0);
}

t_data	init_data(int argc, char **argv)
{
	t_data	ph_data;

	return (ph_data);
}

t_philo	*init_philo(t_data *ph_data)
{
	t_philo	*thinker;

	return (thinker);
}
