/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:43:50 by cpapot            #+#    #+#             */
/*   Updated: 2023/01/23 00:54:29 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	print_error(char *error)
{
	write(2, RED, ft_strlen(RED));
	write(2, error, ft_strlen(error));
	write(2, WHITE, ft_strlen(WHITE));
	exit(1);
}

void	check_error(int argc, char **argv)
{
	int	i;
	int	u;

	i = 1;
	if (argc != 6 && argc != 5)
		print_error("number of arguments is invalid\n");
	while (i != argc)
	{
		u = 0;
		while (argv[i][u])
		{
			if (!(argv[i][u] >= '0' && argv[i][u] <= '9'))
				print_error("argument doesn't only contain digits\n");
			u++;
		}
		i++;
	}
}

t_info	parsing(int argc, char **argv)
{
	t_info	info;

	info.nb_of_philo = ft_atoll(argv[1]);
	if (info.nb_of_philo > INT_MAX || info.nb_of_philo <= 1)
		print_error("nb of philo is invalid\n");
	info.time_to_die = ft_atoll(argv[2]);
	if (info.time_to_die > INT_MAX || info.time_to_die <= 0)
		print_error("time do die is invalid\n");
	info.time_to_eat = ft_atoll(argv[3]);
	if (info.time_to_eat > INT_MAX || info.time_to_eat <= 0)
		print_error("time do eat is invalid\n");
	info.time_to_sleep = ft_atoll(argv[4]);
	if (info.time_to_sleep > INT_MAX || info.time_to_sleep <= 0)
		print_error("time do sleep is invalid\n");
	if (argc == 6)
	{
		info.nb_philo_eat = ft_atoll(argv[5]);
		if (info.nb_philo_eat > INT_MAX || info.nb_philo_eat <= 0)
			print_error("nb philosopher must eat is invalid\n");
	}
	else
		info.nb_philo_eat = -1;
	return (info);
}
