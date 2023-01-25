/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:51:48 by cpapot            #+#    #+#             */
/*   Updated: 2023/01/25 15:55:18 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long long	ft_atoll(const char *str)
{
	long long	result;
	long long	tmp;
	char		is_negative;

	while (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == ' ')
		str++;
	is_negative = *str == '-';
	if (*str == '+' || *str == '-')
		str++;
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		tmp = result * 10 + *str++ - '0';
		if (tmp < result)
		{
			if (is_negative)
				return (LLONG_MIN);
			return (LLONG_MAX);
		}
		result = tmp;
	}
	if (is_negative)
		return (-result);
	return (result);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

t_philo	*ft_philonew(int content, t_info *info)
{
	t_philo			*node;

	node = malloc(sizeof(t_philo));
	if (node == NULL)
		print_error("memory error\n");
	node->actual_philo = content;
	node->eat_count = 0;
	node->info = info;
	return (node);
}
