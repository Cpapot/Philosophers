/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:21:30 by cpapot            #+#    #+#             */
/*   Updated: 2023/02/24 15:40:14 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

pthread_t	*create_philo(t_info *info, t_memlist **memlist)
{
	int				i;
	t_philo			*tmp;
	pthread_t		*philo;
	struct timeval	time;

	i = 0;
	philo = stock_malloc(sizeof(pthread_t) * (info->nb_of_philo), memlist);
	if (philo == NULL)
		print_error("memory error\n");
	info->fork_mutex = create_fork_tab(info->nb_of_philo, memlist);
	info->is_alive = 1;
	gettimeofday(&time, NULL);
	info->creation_time = (long)(time.tv_usec / 1000 + time.tv_sec * 1000);
	while (i != info->nb_of_philo)
	{
		tmp = ft_philonew(i + 1, info, memlist);
		pthread_create (& philo[i], NULL, philo_process, tmp);
		i++;
	}
	return (philo);
}

void	create_mutex(t_info *info)
{
	pthread_mutex_t		dead_mutex;

	pthread_mutex_init(&dead_mutex, NULL);
	info->dead_mutex = dead_mutex;
}

int	main(int argc, char **argv)
{
	t_info				info;
	pthread_t			*philo;
	int					i;
	t_memlist			*memlist;

	memlist = NULL;
	check_error(argc, argv);
	info = parsing(argc, argv);
	create_mutex(&info);
	philo = create_philo(&info, &memlist);
	i = 0;
	while (i != info.nb_of_philo)
	{
		pthread_join (philo [i], NULL);
		i++;
	}
	pthread_mutex_destroy(&info.dead_mutex);
	i = 0;
	while (i != info.nb_of_philo)
	{
		pthread_mutex_destroy (&info.fork_mutex [i]);
		i++;
	}
	stock_free (&memlist);
}
