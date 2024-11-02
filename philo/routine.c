/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:34:04 by izanoni           #+#    #+#             */
/*   Updated: 2024/11/02 15:30:54 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitoring(t_philo *thinker)
{
	int	i;

	i = 0;
	while (!someone_died(thinker->ph_data) && !satisfaction(thinker))
	{
		usleep(100);
		if (i == thinker->ph_data->philo_range)
			i = 0;
		if (get_time(&thinker[i]) > thinker[i].ph_data->time_to_die)
		{
			global_print(&thinker[i], DIED);
			pthread_mutex_lock(&thinker[i].ph_data->mutex_alive);
			thinker[i].ph_data->dead_or_alive = 1;
			pthread_mutex_unlock(&thinker[i].ph_data->mutex_alive);
			break ;
		}
		i++;
	}
}

void	*routine(void *arg)
{
	t_philo	*thinker;

	thinker = (t_philo *)arg;
	pthread_mutex_lock(&thinker->mutex_meal);
	thinker->last_meal = get_milisec();
	pthread_mutex_unlock(&thinker->mutex_meal);
	while (!someone_died(thinker->ph_data))
	{
		pthread_mutex_lock(&thinker->mutex_ate);
		if (thinker->ph_data->max_time_to_eat == thinker->ate)
		{
			pthread_mutex_unlock(&thinker->mutex_ate);
			break ;
		}
		pthread_mutex_unlock(&thinker->mutex_ate);
		philo_meal(thinker);
		if (someone_died(thinker->ph_data) == 1)
			break ;
		bed_time(thinker);
		if (someone_died(thinker->ph_data) == 1)
			break ;
		work_time(thinker);
	}
	return (NULL);
}

void	bed_time(t_philo *thinker)
{
	global_print(thinker, SLEEP);
	usleep(thinker->ph_data->time_to_sleep * 1000);
}

void	work_time(t_philo *thinker)
{
	global_print(thinker, THINK);
	usleep(500);
}

void	philo_meal(t_philo *thinker)
{
	if (thinker->philo_id % 2 == 1)
	{
		pthread_mutex_lock(&thinker->left_fork);
		global_print(thinker, TAKE_FORKS);
		pthread_mutex_lock(thinker->right_fork);
		global_print(thinker, TAKE_FORKS);
	}
	else
	{
		pthread_mutex_lock(thinker->right_fork);
		global_print(thinker, TAKE_FORKS);
		pthread_mutex_lock(&thinker->left_fork);
		global_print(thinker, TAKE_FORKS);
	}
	global_print(thinker, EAT);
	pthread_mutex_lock(&thinker->mutex_meal);
	thinker->last_meal = get_milisec();
	pthread_mutex_unlock(&thinker->mutex_meal);
	usleep(thinker->ph_data->time_to_eat * 1000);
	pthread_mutex_lock(&thinker->mutex_ate);
	thinker->ate++;
	pthread_mutex_unlock(&thinker->mutex_ate);
	pthread_mutex_unlock(&thinker->left_fork);
	pthread_mutex_unlock(thinker->right_fork);
}
