/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:35:52 by aobshatk          #+#    #+#             */
/*   Updated: 2025/07/11 23:23:42 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vbc.h"

t_list	*new_nd(char c)
{
	t_list *new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->val = c;
	new_node->next = NULL;
	return new_node;
}

void	add_node(t_list **head, t_list *node)
{
	if (!node)
		return;
	if (!*head)
	{
		*head = node;
		return;
	}
	t_list *temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = node;
}

void	free_list(t_list **head)
{
	if (!head)
		return;
	t_list *temp;
	while (*head)
	{
		temp = (*head)->next;
		free(*head);
		*head = temp;
	}
}

int list_size(t_list *list)
{
	int size = 0;
	while (list)
	{
		size++;
		list = list->next;
	}
	return size;
}