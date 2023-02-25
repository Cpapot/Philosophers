/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:00:24 by cpapot            #+#    #+#             */
/*   Updated: 2023/02/25 17:01:44 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static int	is_dead(t_philo *info)
{
	long			tmp;
	struct timeval	time;

	pthread_mutex_lock (& info->info->dead_mutex);
	gettimeofday(&time, NULL);
	tmp = (long)(time.tv_usec * 0.001 + time.tv_sec * 1000)
		- info->info->creation_time;
	if ((tmp - (long)info->last_eat > info->info->time_to_die
			&& info->info->is_alive != 0) || info->info->nb_of_philo == 1)
	{
		lock_print(info, DEAD, info->actual_philo);
		info->info->is_alive = 0;
	}
	if (info->info->is_alive == 0)
	{
		pthread_mutex_unlock (& info->info->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock (& info->info->dead_mutex);
	return (0);
}

static void	smart_usleep(t_philo *info, int sleeptime)
{
	struct timeval	time;
	long			tmp;

	gettimeofday(&time, NULL);
	tmp = (long)(time.tv_usec * 0.001 + time.tv_sec * 1000)
		- info->info->creation_time;
	if (tmp - info->last_eat + sleeptime > info->info->time_to_die)
		usleep((info->info->time_to_die - (tmp - info->last_eat) + 1) * 1000);
	else
		usleep(sleeptime * 1000);
}

static int	eat_philo(t_philo *info)
{
	struct timeval	time;
	long			tmp;

	check_fork(info);
	lock_print(info, FORK, info->actual_philo);
	lock_print(info, FORK, info->actual_philo);
	pthread_mutex_lock (& info->info->dead_mutex);
	gettimeofday(&time, NULL);
	tmp = (long)(time.tv_usec * 0.001 + time.tv_sec * 1000)
		- info->info->creation_time;
	if (tmp - info->last_eat > info->info->time_to_die
		|| info->info->is_alive == 0)
	{
		pthread_mutex_unlock (& info->info->dead_mutex);
		reset_fork(info);
		return (0);
	}
	pthread_mutex_unlock (& info->info->dead_mutex);
	lock_print(info, EAT, info->actual_philo);
	info->eat_count++;
	set_last_eat(info);
	smart_usleep(info, info->info->time_to_eat);
	reset_fork(info);
	return (1);
}

int	sleep_and_think(t_philo	*info)
{
	if (is_dead(info))
		return (1);
	lock_print(info, SLEEP, info->actual_philo);
	smart_usleep(info, info->info->time_to_sleep);
	if (is_dead(info))
		return (1);
	lock_print(info, THINK, info->actual_philo);
	if (info->info->nb_of_philo % 2 == 1)
		usleep((info->info->nb_philo_eat / 10) * 10);
	return (0);
}

void	*philo_process(void *p_data)
{
	t_philo			*info;

	info = (t_philo *)p_data;
	if (info->info->nb_of_philo == 1)
	{
		lock_print(info, FORK, info->actual_philo);
		usleep(info->info->time_to_die * 1000);
		if (is_dead(info))
			return (0);
	}
	if (info->actual_philo % 2)
		usleep(15000);
	while (info->eat_count != info->info->nb_philo_eat)
	{
		info->can_eat = 0;
		if (eat_philo(info))
		{
			if (sleep_and_think(info))
				return (p_data);
		}
		if (is_dead(info))
			return (p_data);
	}
	return (p_data);
}
