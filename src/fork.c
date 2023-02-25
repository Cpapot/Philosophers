/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:56:09 by cpapot            #+#    #+#             */
/*   Updated: 2023/02/25 17:03:38 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

pthread_mutex_t	*create_fork_tab(int philo_nb, t_memlist **memlist)
{
	pthread_mutex_t	*mutex_fork;
	int				i;

	mutex_fork = stock_malloc(sizeof(pthread_mutex_t) * (philo_nb), memlist);
	if (mutex_fork == NULL)
		print_error("memory error\n");
	i = 0;
	while (i != philo_nb)
	{
		pthread_mutex_init(& mutex_fork[i], NULL);
		i++;
	}
	return (mutex_fork);
}

void	check_fork(t_philo *info)
{
	if (info->info->nb_of_philo != 1)
	{
		pthread_mutex_lock (& info->info->dead_mutex);
		if (info->info->is_alive == 0)
		{
			pthread_mutex_unlock (& info->info->dead_mutex);
			exit (1);
		}
		pthread_mutex_unlock (& info->info->dead_mutex);
		pthread_mutex_lock (& info->info->fork_mutex[info->right_fork]);
		pthread_mutex_lock (& info->info->dead_mutex);
		if (info->info->is_alive == 0)
		{
			pthread_mutex_unlock (& info->info->dead_mutex);
			pthread_mutex_unlock (& info->info->fork_mutex[info->right_fork]);
			exit (1);
		}
		pthread_mutex_unlock (& info->info->dead_mutex);
		pthread_mutex_lock (& info->info->fork_mutex[info->left_fork]);
	}
}

void	reset_fork(t_philo *info)
{
	if (info->info->nb_of_philo != 1)
	{
		pthread_mutex_unlock (& info->info->fork_mutex[info->left_fork]);
		pthread_mutex_unlock (& info->info->fork_mutex[info->right_fork]);
	}
}
