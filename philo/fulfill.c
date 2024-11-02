/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fulfill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:45:39 by izanoni           #+#    #+#             */
/*   Updated: 2024/11/02 14:59:07 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	init_data(char **argv)
{
	t_data	ph_data;

	ph_data.philo_range = philo_atoi(argv[1]);
	ph_data.time_to_die = philo_atoi(argv[2]);
	ph_data.time_to_eat = philo_atoi(argv[3]);
	ph_data.time_to_sleep = philo_atoi(argv[4]);
	if (argv[5])
		ph_data.max_time_to_eat = philo_atoi(argv[5]);
	else
		ph_data.max_time_to_eat = -1;
	ph_data.dead_or_alive = 0;
	pthread_mutex_init(&ph_data.mutex_alive, NULL);
	pthread_mutex_init(&ph_data.mutex_print, NULL);
	return (ph_data);
}

t_philo	*init_philo(int philos, t_data *ph_data)
{
	t_philo	*thinker;
	int		count;
	int		id;

	id = 1;
	count = 0;
	thinker = (t_philo *) malloc ((philos) * sizeof (t_philo));
	if (!thinker)
		return (NULL);
	while (count < philos)
	{
		thinker[count].ph_data = ph_data;
		thinker[count].philo_id = id;
		thinker[count].right_fork = &thinker[(count + 1) % philos].left_fork;
		thinker[count].ate = 0;
		thinker[count].last_meal = get_milisec();
		pthread_mutex_init(&thinker[count].left_fork, NULL);
		pthread_mutex_init(&thinker[count].mutex_meal, NULL);
		pthread_mutex_init(&thinker[count].mutex_ate, NULL);
		count++;
		id++;
	}
	return (thinker);
}

long	get_milisec(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	global_print(t_philo *thinker, char *action)
{
	if (!someone_died(thinker->ph_data))
	{
		pthread_mutex_lock(&thinker->ph_data->mutex_print);
		printf("%ld %d %s\n", get_milisec() - thinker->ph_data->start_time,
			thinker->philo_id, action);
		pthread_mutex_unlock(&thinker->ph_data->mutex_print);
	}
}
