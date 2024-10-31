/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:34:04 by izanoni           #+#    #+#             */
/*   Updated: 2024/10/30 18:58:28 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_routine(t_philo *thinker)
{
	int	i;

	i = 0;
	while (i < thinker->ph_data->philo_range)
	{
		pthread_create(&thinker[i].self_thread, NULL, routine, &thinker[i]);
		i++;
	}
	i = 0;
	while (1)	// monitor
	{
		if (i == thinker->ph_data->philo_range)
			i = 0;
		if (get_milisec() - thinker[i].last_meal  > thinker->ph_data->time_to_die)
		{
			pthread_mutex_lock(&thinker->ph_data->mutex_alive);
			thinker->ph_data->dead_or_alive = 1;
			pthread_mutex_unlock(&thinker->ph_data->mutex_alive);
			break;
		}
		i++;
	}
	i = 0;
	while (i < thinker->ph_data->philo_range)
	{
		pthread_join(thinker[i].self_thread, NULL);
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
		global_print(get_milisec(), thinker, SLEEP);
		usleep(thinker->ph_data->time_to_sleep * 1000);
		global_print(get_milisec(), thinker, THINK);
		usleep(1000);
		i++;
	}
	return(NULL);
}

void philo_meal(t_philo *thinker)
{
	if (thinker->philo_id % 2 == 1)
	{
		pthread_mutex_lock(&thinker->left_fork);
		pthread_mutex_lock(thinker->right_fork);
		global_print(get_milisec(), thinker, TAKE_FORKS);
		global_print(get_milisec(), thinker, TAKE_FORKS);
	}
	else
	{
		pthread_mutex_lock(thinker->right_fork);
		pthread_mutex_lock(&thinker->left_fork);
		global_print(get_milisec(), thinker, TAKE_FORKS);
		global_print(get_milisec(), thinker, TAKE_FORKS);
	}
	global_print(get_milisec(), thinker, EAT);
	usleep(thinker->ph_data->time_to_eat * 1000);
	pthread_mutex_lock(&thinker->mutex_meal);
	thinker->last_meal = get_milisec();
	pthread_mutex_unlock(&thinker->mutex_meal);
	pthread_mutex_unlock(&thinker->left_fork);
	pthread_mutex_unlock(thinker->right_fork);
}

void	last_meal(t_philo *thinker)
{
	pthread_mutex_lock(&thinker->mutex_meal);
	thinker->last_meal = get_milisec();
	pthread_mutex_unlock(&thinker->mutex_meal);
}
