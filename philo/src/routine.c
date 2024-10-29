/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:34:04 by izanoni           #+#    #+#             */
/*   Updated: 2024/10/29 20:24:38 by izanoni          ###   ########.fr       */
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
	// monitor
	i = 0;
	while (i < thinker->ph_data->philo_range)
	{
		pthread_join(thinker[i].thread, NULL);
		i++;
	}
	destroy_mutex(thinker);
}

void destroy_mutex(t_philo *thinker)
{
	int	i;
	
	i = 0;
	while (i < thinker->ph_data->philo_range)
	{
		pthread_mutex_destroy(&thinker[i].mutex_meal);
		pthread_mutex_destroy(&thinker[i].left_fork);
		i++;
	}
	pthread_mutex_destroy(&thinker->ph_data->mutex_alive);
	pthread_mutex_destroy(&thinker->ph_data->mutex_print);
}

void *routine(void *arg)
{
	t_philo *thinker;
	int i;
	
	i = 0;
	thinker = arg;
	while(i < 10 )
	{
		philo_meal(thinker);
		printf ("%ld philo %d is sleeping\n",
			get_milisec() - thinker->ph_data->start_time, thinker->philo_id);
		usleep(thinker->ph_data->time_to_sleep * 1000);
		printf ("%ld philo %d is thinking\n",
			get_milisec() - thinker->ph_data->start_time, thinker->philo_id);
		i++;	
	}
	return(NULL);
}

void philo_meal(t_philo *thinker)
{
	if(thinker->philo_id % 2 == 1)
	{
		pthread_mutex_lock(&thinker->left_fork);
		printf("%ld philo %d has taken a fork\n",
			get_milisec() - thinker->ph_data->start_time, thinker->philo_id);
		pthread_mutex_lock(thinker->right_fork);
		printf("%ld philo %d has taken a fork\n",
			get_milisec() - thinker->ph_data->start_time, thinker->philo_id);
	}
	else
	{
		pthread_mutex_lock(thinker->right_fork);
		printf("%ld philo %d has taken a fork\n",
			get_milisec() - thinker->ph_data->start_time, thinker->philo_id);
		pthread_mutex_lock(&thinker->left_fork);
		printf("%ld philo %d has taken a fork\n",
			get_milisec() - thinker->ph_data->start_time, thinker->philo_id);
	}
	printf ("%ld philo %d is eating\n",
			get_milisec() - thinker->ph_data->start_time, thinker->philo_id);
	usleep(thinker->ph_data->time_to_eat * 1000);
	pthread_mutex_unlock(&thinker->left_fork);
	pthread_mutex_unlock(thinker->right_fork);
}
