/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:02:51 by izanoni           #+#    #+#             */
/*   Updated: 2024/10/21 20:14:07 by izanoni          ###   ########.fr       */
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
		ph_data = init_data(argv);
		thinker = init_philo(philo_atoi(argv[1]), &ph_data);
	}	
	return (0);
}

t_data	init_data(char **argv)
{
	t_data	ph_data;

	ph_data.time_to_die = philo_atoi(argv[2]);
	ph_data.time_to_eat = philo_atoi(argv[3]);
	ph_data.time_to_sleep = philo_atoi(argv[4]);
	if (argv[5])
		ph_data.max_time_to_eat = philo_atoi(argv[5]);
	else
		ph_data.max_time_to_eat = -1;
	return (ph_data);
}

t_philo	*init_philo(int philos, t_data *ph_data)
{
	t_philo	*thinker;
	int	count;
	
	count = 0;
	thinker = (t_philo *) malloc ((philos + 1) * sizeof (t_philo));
	if (!thinker)
		return(NULL);
	while (count <= philos)
	{
		thinker[count].ph_data = ph_data;
		count++;
	}	
	return (thinker);
}
