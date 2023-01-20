/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:43:50 by cpapot            #+#    #+#             */
/*   Updated: 2023/01/20 19:30:39 by cpapot           ###   ########.fr       */
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
