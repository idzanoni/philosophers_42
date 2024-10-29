/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:34:04 by izanoni           #+#    #+#             */
/*   Updated: 2024/10/29 16:30:48 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_routine(t_philo *thinker)
{
	int	i;

	i = 0;
	pthread_mutex_init(&thinker->ph_data->mutex_alive, NULL);
	pthread_mutex_init(&thinker->ph_data->mutex_print, NULL);
	while (i < thinker->ph_data->philo_range)
	{
		pthread_create(&thinker[i].thread, NULL, routine, &thinker[i]);
		i++;
	}
	i = 0;
	while (i < thinker->ph_data->philo_range)
	{
		pthread_join(thinker[i].thread, NULL);
		i++;
	}
	return ;
}

void *routine(void *arg)
{
	t_philo *thinker;

	thinker = arg;
	printf ("eating\n");
	printf ("sleeping\n");
	printf ("thinking\n");
	return(NULL);
}