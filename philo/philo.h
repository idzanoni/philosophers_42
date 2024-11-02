/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:43:24 by izanoni           #+#    #+#             */
/*   Updated: 2024/11/02 15:34:15 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TAKE_FORKS "has taken a fork"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define EAT "is eating"
# define DIED "died"

typedef struct s_data
{
	long			start_time;
	int				philo_range;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_time_to_eat;
	int				dead_or_alive;
	pthread_mutex_t	mutex_alive;
	pthread_mutex_t	mutex_print;
}	t_data;

typedef struct s_philo
{
	t_data			*ph_data;
	int				philo_id;
	int				ate;
	pthread_mutex_t	mutex_ate;
	pthread_t		self_thread;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	long			last_meal;
	pthread_mutex_t	mutex_meal;
}	t_philo;

//philo
void	lonely_philo(t_philo *thinker);
void	init_routine(t_philo *thinker);

//philo_lib
int		philo_isdigit(int i);
int		philo_atoi(const char *nptr);

//check
int		check_input(int argc, char **argv);
int		number_of_args(int argc);
int		min_time(char **argv);
int		max_min_philo(char	**argv);
int		args_is_num(char **argv);

//routine
void	monitoring(t_philo *thinker);
void	*routine(void *arg);
void	philo_meal(t_philo *thinker);
void	bed_time(t_philo *thinker);
void	work_time(t_philo *thinker);

//aux
void	destroy_mutex(t_philo *thinker);
long	get_time(t_philo *thinker);
int		satisfaction(t_philo *thinker);
int		someone_died(t_data *ph_data);
void	last_meal(t_philo *thinker);

//fulfill
t_data	init_data(char **argv);
t_philo	*init_philo(int philos, t_data *ph_data);
long	get_milisec(void);
void	global_print(t_philo *thinker, char *action);

#endif
