/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:02:54 by izanoni           #+#    #+#             */
/*   Updated: 2024/11/02 15:03:57 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_philo *thinker)
{
	long	time;

	pthread_mutex_lock(&thinker->mutex_meal);
	time = get_milisec() - thinker->last_meal;
	pthread_mutex_unlock(&thinker->mutex_meal);
	return (time);
}

int	satisfaction(t_philo *thinker)
{
	int	i;

	i = 0;
	while (i < thinker->ph_data->philo_range)
	{
		pthread_mutex_lock(&thinker[i].mutex_ate);
		if (thinker[i].ate != thinker[i].ph_data->max_time_to_eat)
		{
			pthread_mutex_unlock(&thinker[i].mutex_ate);
			return (0);
		}
		pthread_mutex_unlock(&thinker[i].mutex_ate);
		i++;
	}
	return (1);
}

void	destroy_mutex(t_philo *thinker)
{
	int	i;

	i = 0;
	while (i < thinker->ph_data->philo_range)
	{
		pthread_mutex_destroy(&thinker[i].mutex_meal);
		pthread_mutex_destroy(&thinker[i].left_fork);
		pthread_mutex_destroy(&thinker[i].mutex_ate);
		i++;
	}
	pthread_mutex_destroy(&thinker->ph_data->mutex_alive);
	pthread_mutex_destroy(&thinker->ph_data->mutex_print);
}

void	last_meal(t_philo *thinker)
{
	pthread_mutex_lock(&thinker->mutex_meal);
	thinker->last_meal = get_milisec();
	pthread_mutex_unlock(&thinker->mutex_meal);
}

int	someone_died(t_data *ph_data)
{
	int	coffin;

	pthread_mutex_lock(&ph_data->mutex_alive);
	coffin = ph_data->dead_or_alive;
	pthread_mutex_unlock(&ph_data->mutex_alive);
	return (coffin);
}
