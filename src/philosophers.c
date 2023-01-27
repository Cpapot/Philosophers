/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:21:30 by cpapot            #+#    #+#             */
/*   Updated: 2023/01/27 16:38:33 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

pthread_t	*create_philo(t_info *info)
{
	int				i;
	t_philo			*tmp;
	pthread_t		*philo;
	struct timeval	time;

	i = 0;
	philo = malloc(sizeof(pthread_t) * (info->nb_of_philo));
	if (philo == NULL)
		print_error("memory error\n");
	info->fork_tab = create_fork_tab(info->nb_of_philo);
	info->is_alive = 1;
	gettimeofday(&time, NULL);
	info->creation_time = (long)(time.tv_usec / 1000 + time.tv_sec * 1000);
	while (i != info->nb_of_philo)
	{
		tmp = ft_philonew(i + 1, info);
		pthread_create (& philo[i], NULL, philo_process, tmp);
		i++;
	}
	return (philo);
}

int	main(int argc, char **argv)
{
	t_info				info;
	pthread_t			*philo;
	int					i;
	pthread_mutex_t		mutex;

	check_error(argc, argv);
	info = parsing(argc, argv);
	pthread_mutex_init(&mutex, NULL);
	info.mutex = mutex;
	info.is_free = 0;
	philo = create_philo(&info);
	i = 0;
	while (i != info.nb_of_philo)
	{
		pthread_join (philo [i], NULL);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	free (philo);
}
