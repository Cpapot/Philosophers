/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:00:24 by cpapot            #+#    #+#             */
/*   Updated: 2023/01/25 17:30:36 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	eat_philo(t_philo *info)
{
	long			tmp;
	struct timeval	time;

	check_fork(info);
	gettimeofday(&time, NULL);
	tmp = (long)(time.tv_usec * 0.001 + time.tv_sec * 1000)
		- info->info->creation_time;
	printf(CYAN"%ld %d has taken a fork\n", tmp, info->actual_philo);
	printf(CYAN"%ld %d has taken a fork\n", tmp, info->actual_philo);
	gettimeofday(&time, NULL);
	tmp = (long)(time.tv_usec * 0.001 + time.tv_sec * 1000);
	printf(GREEN"%ld %d is eating\n", tmp - info->info->creation_time,
		info->actual_philo);
	pthread_mutex_unlock (& info->info->mutex);
	usleep(info->info->time_to_eat * 1000);
	reset_fork(info);
	info->eat_count++;
	info->last_eat = tmp - info->info->creation_time;
}

static void	fininsh_philo(t_philo *info)
{
	pthread_mutex_lock (& info->info->mutex);
	if (info->info->is_alive != 1)
	{
		free(info);
		pthread_mutex_unlock (& info->info->mutex);
		exit(EXIT_SUCCESS);
	}
	pthread_mutex_unlock (& info->info->mutex);
}

static void	is_dead(t_philo *info)
{
	long			tmp;
	struct timeval	time;


	gettimeofday(&time, NULL);
	pthread_mutex_lock (& info->info->mutex);
	tmp = (long)(time.tv_usec * 0.001 + time.tv_sec * 1000)
		- info->info->creation_time;
	if (tmp - (long)info->last_eat > info->info->time_to_die)
	{
		printf(BLACK"%ld %d is dead\n", tmp, info->actual_philo);
		info->info->is_alive = 0;
		free(info->info->fork_tab);
	}
	pthread_mutex_unlock (& info->info->mutex);
}

void	*philo_process(void *p_data)
{
	t_philo			*info;
	struct timeval	time;
	long			tmp;

	info = (t_philo *)p_data;
	while (info->eat_count != info->info->nb_philo_eat)
	{
		eat_philo(info);
		is_dead(info);
		fininsh_philo(info);
		gettimeofday(&time, NULL);
		tmp = (long)(time.tv_usec * 0.001 + time.tv_sec * 1000)
			- info->info->creation_time;
		printf(MAGENTA"%ld %d is sleeping\n", tmp, info->actual_philo);
		usleep(info->info->time_to_sleep * 1000);
		gettimeofday(&time, NULL);
		tmp = (long)(time.tv_usec * 0.001 + time.tv_sec * 1000)
			- info->info->creation_time;
		printf(YELLOW"%ld %d is thinking\n", tmp, info->actual_philo);
		is_dead(info);
		fininsh_philo(info);
	}
	return (p_data);
}