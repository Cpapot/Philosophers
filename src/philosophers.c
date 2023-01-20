/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:21:30 by cpapot            #+#    #+#             */
/*   Updated: 2023/01/20 22:47:02 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	*philo_process(void *p_data)
{
	int	*philo_id;
	int	tmp;

	philo_id = (int *)p_data;
	tmp = *philo_id;
	printf("philo nb :%d created\n", tmp);
	return (p_data);
}

pthread_t	*create_philo(t_info info)
{
	int			i;
	pthread_t	*philo;

	i = 0;
	philo = malloc(sizeof(pthread_t) * (info.nb_of_philo));
	if (philo == NULL)
		print_error("memory error\n");
	while (i != info.nb_of_philo)
	{
		pthread_create (& philo [i], NULL, philo_process, &i);
		i++;
	}
	return (philo);
}

int	main(int argc, char **argv)
{
	t_info		info;
	pthread_t	*philo;
	int			i;

	check_error(argc, argv);
	info = parsing(argc, argv);
	philo = create_philo(info);
	i = 0;
	while (i != info.nb_of_philo)
	{
		pthread_join (philo [i], NULL);
		i++;
	}
	free (philo);
}
