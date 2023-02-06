/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:00:24 by cpapot            #+#    #+#             */
/*   Updated: 2023/02/06 19:02:14 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	kill_philo(t_philo *info)
{
	pthread_mutex_lock (& info->info->dead_mutex);
	if (info->info->is_free == 0)
	{
		free(info->info->fork_tab);
		info->info->is_free = 0;
	}
	pthread_mutex_unlock (& info->info->dead_mutex);
	free(info);
	exit(EXIT_SUCCESS);
}

static void	is_dead(t_philo *info)
{
	//long			tmp;
	struct timeval	time;

	gettimeofday(&time, NULL);
	/*tmp = (long)(time.tv_usec * 0.001 + time.tv_sec * 1000)
		- info->info->creation_time;
	if (tmp == 0)
		tmp = 0;
	if ((tmp - (long)info->last_eat > info->info->time_to_die
			&& info->info->is_alive != 0) || info->info->nb_of_philo == 1)
	{
		pthread_mutex_lock (& info->info->dead_mutex);
		printf(WHITE"%ld %d is dead\n", tmp, info->actual_philo);
		info->info->is_alive = 0;
		free(info->info->fork_tab);
		info->info->is_free = 1;
		pthread_mutex_unlock (& info->info->dead_mutex);
	}*/
	if (info->info->is_alive != 1)
		kill_philo(info);
}

static void	eat_philo(t_philo *info)
{
	long			tmp;
	struct timeval	time;

	while (info->can_eat == 0)
	{
		check_fork(info);
		if (info->can_eat == 1)
		{
			gettimeofday(&time, NULL);
			tmp = (long)(time.tv_usec * 0.001 + time.tv_sec * 1000)
				- info->info->creation_time;
			printf(CYAN"%ld %d has taken a fork\n", tmp, info->actual_philo);
			printf(CYAN"%ld %d has taken a fork\n", tmp, info->actual_philo);
			gettimeofday(&time, NULL);
			tmp = (long)(time.tv_usec * 0.001 + time.tv_sec * 1000);
			printf(GREEN"%ld %d is eating\n", tmp - info->info->creation_time,
				info->actual_philo);
			usleep(info->info->time_to_eat * 1000);
			info->eat_count++;
			info->last_eat = tmp - info->info->creation_time;
		}
		is_dead(info);
	}
	reset_fork(info);
}

void	sleep_and_think(t_philo	*info)
{
	struct timeval	time;
	long			tmp;

	is_dead(info);
	gettimeofday(&time, NULL);
	tmp = (long)(time.tv_usec * 0.001 + time.tv_sec * 1000)
		- info->info->creation_time;
	printf(MAGENTA"%ld %d is sleeping\n", tmp, info->actual_philo);
	usleep(info->info->time_to_sleep * 1000);
	is_dead(info);
	gettimeofday(&time, NULL);
	tmp = (long)(time.tv_usec * 0.001 + time.tv_sec * 1000)
		- info->info->creation_time;
	printf(YELLOW"%ld %d is thinking\n", tmp, info->actual_philo);
	if (info->info->nb_of_philo % 2 == 1)
		usleep((info->info->nb_philo_eat / 10) * 10);
}

void	*philo_process(void *p_data)
{
	t_philo			*info;

	info = (t_philo *)p_data;
	is_dead(info);
	if (info->actual_philo % 2)
		usleep(15000);
	while (info->eat_count != info->info->nb_philo_eat)
	{
		pthread_mutex_lock (& info->info->status_mutex);
		info->can_eat = 0;
		pthread_mutex_unlock (& info->info->status_mutex);
		eat_philo(info);
		sleep_and_think(info);
	}
	kill_philo(info);
	return (p_data);
}
