/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:02:09 by cpapot            #+#    #+#             */
/*   Updated: 2023/01/24 17:31:10 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	check_fork(t_philo *info)
{
	int	tmp;

	tmp = 0;
	while (tmp == 0)
	{
		if (info->actual_philo == 1 && info->info->fork_tab[0] == 1
			&& info->info->fork_tab[info->info->nb_of_philo - 1])
		{
			pthread_mutex_lock (& info->info->mutex);
			info->info->fork_tab[0] = 0;
			info->info->fork_tab[info->info->nb_of_philo - 1] = 0;
			tmp = 1;
			pthread_mutex_unlock (& info->info->mutex);
		}
		else if (info->info->fork_tab[info->actual_philo - 1] == 1
			&& info->info->fork_tab[info->actual_philo - 2] == 1)
		{
			pthread_mutex_lock (& info->info->mutex);
			info->info->fork_tab[info->actual_philo - 1] = 0;
			info->info->fork_tab[info->actual_philo - 2] = 0;
			tmp = 1;
			pthread_mutex_unlock (& info->info->mutex);
		}
	}
}

static void	reset_fork(t_philo *info)
{
	if (info->actual_philo == 1 && info->info->fork_tab[0] == 0
		&& info->info->fork_tab[info->info->nb_of_philo - 1] == 0)
	{
		pthread_mutex_lock (& info->info->mutex);
		info->info->fork_tab[0] = 1;
		info->info->fork_tab[info->info->nb_of_philo - 1] = 1;
		pthread_mutex_unlock (& info->info->mutex);
	}
	else if (info->info->fork_tab[info->actual_philo - 1] == 0
		&& info->info->fork_tab[info->actual_philo - 2] == 0)
	{
		pthread_mutex_lock (& info->info->mutex);
		info->info->fork_tab[info->actual_philo - 1] = 1;
		info->info->fork_tab[info->actual_philo - 2] = 1;
		pthread_mutex_unlock (& info->info->mutex);
	}
}

void	eat_philo(t_philo *info)
{
	long			tmp;
	struct timeval	time;

	check_fork(info);
	gettimeofday(&time, NULL);
	tmp = (long)(time.tv_usec / 1000 + time.tv_sec * 1000)
		- info->creation_time;
	printf("%ld %d has taken a fork\n", tmp, info->actual_philo);
	printf("%ld %d has taken a fork\n", tmp, info->actual_philo);
	gettimeofday(&time, NULL);
	tmp = (long)(time.tv_usec / 1000 + time.tv_sec * 1000);
	printf("%ld %d is eating\n", tmp - info->creation_time, info->actual_philo);
	usleep(info->info->time_to_eat * 1000);
	info->eat_count++;
	reset_fork(info);
}
