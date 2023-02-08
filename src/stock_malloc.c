/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:10:24 by cpapot            #+#    #+#             */
/*   Updated: 2023/02/08 17:12:02 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	lst_mem_add(t_memlist **lst, t_memlist *new)
{
	t_memlist	*last;

	if (new == NULL || lst == NULL)
		return ;
	last = *lst;
	if (last == NULL)
		*lst = new;
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

t_memlist	*lst_mem_new(void *content)
{
	t_memlist	*node;

	node = malloc(sizeof(t_memlist));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	*stock_malloc(size_t size, t_memlist **stock)
{
	void		*result;
	t_memlist	*tmp;

	result = malloc(size);
	if (result == NULL)
		return (NULL);
	if (*stock == NULL)
		*stock = lst_mem_new(result);
	else
	{
		tmp = lst_mem_new(result);
		lst_mem_add(stock, tmp);
	}
	return (result);
}
