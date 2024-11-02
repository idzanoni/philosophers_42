/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:02:51 by izanoni           #+#    #+#             */
/*   Updated: 2024/11/02 15:28:03 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	ph_data;
	t_philo	*thinker;

	if (check_input(argc, argv) == 0)
	{
		ph_data = init_data(argv);
		thinker = init_philo(ph_data.philo_range, &ph_data);
		if (ph_data.philo_range == 1)
			lonely_philo(thinker);
		else
			init_routine(thinker);
		free(thinker);
	}
	else
		return (-1);
	return (0);
}

void	lonely_philo(t_philo *thinker)
{
	global_print(thinker, TAKE_FORKS);
	usleep((thinker->ph_data->time_to_die + 1) * 1000);
	global_print(thinker, DIED);
}

void	init_routine(t_philo *thinker)
{
	int	i;

	i = 0;
	thinker->ph_data->start_time = get_milisec();
	while (i < thinker->ph_data->philo_range)
	{
		pthread_create(&thinker[i].self_thread, NULL, routine, &thinker[i]);
		i++;
	}
	monitoring(thinker);
	i = 0;
	while (i < thinker->ph_data->philo_range)
	{
		pthread_join(thinker[i].self_thread, NULL);
		i++;
	}
	destroy_mutex (thinker);
}
