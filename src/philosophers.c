/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:21:30 by cpapot            #+#    #+#             */
/*   Updated: 2023/01/24 20:19:58 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static int	*create_fork_tab(int philo_nb)
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

static void	*philo_process(void *p_data)
{
	t_philo			*info;
	struct timeval	time;
	long			tmp;

	info = (t_philo *)p_data;
	gettimeofday(&time, NULL);
	info->creation_time = (long)(time.tv_usec / 1000 + time.tv_sec * 1000);

	eat_philo(info);
	usleep(info->info->time_to_sleep * 1000);
	gettimeofday(&time, NULL);
	tmp = (long)(time.tv_usec / 1000 + time.tv_sec * 1000)
		- info->creation_time;
	printf(MAGENTA"%ld %d is sleeping\n", tmp, info->actual_philo);
	return (p_data);
}

pthread_t	*create_philo(t_info *info)
{
	int			i;
	t_philo		*tmp;
	pthread_t	*philo;

	i = 0;
	philo = malloc(sizeof(pthread_t) * (info->nb_of_philo));
	if (philo == NULL)
		print_error("memory error\n");
	info->fork_tab = create_fork_tab(info->nb_of_philo);
	info->is_alive = 1;
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
