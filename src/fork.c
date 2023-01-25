/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:56:09 by cpapot            #+#    #+#             */
/*   Updated: 2023/01/25 15:57:50 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	*create_fork_tab(int philo_nb)
{
	int	*fork_tab;
	int	i;

	fork_tab = malloc(sizeof(int) * (philo_nb));
	if (fork_tab == NULL)
		print_error("memory error\n");
	i = 0;
	while (i != philo_nb)
	{
		fork_tab[i] = 1;
		i++;
	}
	return (fork_tab);
}

void	check_fork(t_philo *info)
{
	int	tmp;

	tmp = 0;
	while (tmp == 0)
	{
		pthread_mutex_lock (& info->info->mutex);
		if (info->actual_philo == 1 && info->info->fork_tab[0] == 1
			&& info->info->fork_tab[info->info->nb_of_philo - 1])
		{
			info->info->fork_tab[0] = 0;
			info->info->fork_tab[info->info->nb_of_philo - 1] = 0;
			tmp = 1;
		}
		else if (info->info->fork_tab[info->actual_philo - 1] == 1
			&& info->info->fork_tab[info->actual_philo - 2] == 1)
		{
			info->info->fork_tab[info->actual_philo - 1] = 0;
			info->info->fork_tab[info->actual_philo - 2] = 0;
			tmp = 1;
		}
		pthread_mutex_unlock (& info->info->mutex);
	}
}

void	reset_fork(t_philo *info)
{
	pthread_mutex_lock (& info->info->mutex);
	if (info->actual_philo == 1 && info->info->fork_tab[0] == 0
		&& info->info->fork_tab[info->info->nb_of_philo - 1] == 0)
	{
		info->info->fork_tab[0] = 1;
		info->info->fork_tab[info->info->nb_of_philo - 1] = 1;
	}
	else if (info->info->fork_tab[info->actual_philo - 1] == 0
		&& info->info->fork_tab[info->actual_philo - 2] == 0)
	{
		info->info->fork_tab[info->actual_philo - 1] = 1;
		info->info->fork_tab[info->actual_philo - 2] = 1;
	}
	pthread_mutex_unlock (& info->info->mutex);
}
