/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:02:51 by izanoni           #+#    #+#             */
/*   Updated: 2024/10/29 19:43:40 by izanoni          ###   ########.fr       */
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
		ph_data.start_time = get_milisec();	
		thinker = init_philo(philo_atoi(argv[1]), &ph_data);
		init_routine(thinker);
		
		free(thinker);
	}
	else
		return (-1);
	return (0);
}

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
	return (ph_data);
}

t_philo	*init_philo(int philos, t_data *ph_data)
{
	t_philo	*thinker;
	int	count;
	int id;
	
	id = 1;
	count = 0;
	thinker = (t_philo *) malloc ((philos) * sizeof (t_philo));
	if (!thinker)
		return(NULL);
	while (count < philos)
	{
		thinker[count].ph_data = ph_data;
		thinker[count].philo_id = id;
		thinker[count].right_fork = &thinker[(count + 1) % philos].left_fork;
		pthread_mutex_init(&thinker[count].left_fork, NULL);
		pthread_mutex_init(&thinker[count].mutex_meal, NULL);
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
