/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:27:45 by aobshatk          #+#    #+#             */
/*   Updated: 2025/07/12 13:46:28 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vbc.h"

b_tree	*new_node(b_tree node)
{
	b_tree	*new_node;

	new_node = calloc(sizeof(node), 1);
	if (!new_node)
		return (NULL);
	*new_node = node;
	return (new_node);
}

void	push_tree(b_tree **tree, b_tree node)
{
	b_tree	*temp;

	if (!*tree)
	{
		*tree = new_node(node);
		return ;
	}
	temp = *tree;
	if (temp->type == VAL)
	{
		*tree = new_node(node);
		(*tree)->r = temp;
		return ;
	}
	if (!temp->l)
	{
		(*tree)->l = new_node(node);
		return ;
	}
	if (!temp->r)
	{
		(*tree)->r = new_node(node);
		return ;
	}
	while (temp->l)
	{
		if (add_leaf(temp, node))
			return ;
		temp = temp->l;
	}
	temp = *tree;
	while (temp->r)
	{
		if (add_leaf(temp, node))
			return ;
		temp = temp->r;
	}
}

void	pop_tree(b_tree **tree, b_tree node)
{
	b_tree	*temp;

	if (!*tree)
	{
		*tree = new_node(node);
		return ;
	}
	temp = *tree;
	*tree = new_node(node);
	(*tree)->r = temp;
}

int	add_leaf(b_tree *branch, b_tree leaf)
{
	b_tree	*temp;

	if (!branch->l)
	{
		branch = new_node(leaf);
		return (1);
	}
	if (branch->l && leaf.type != VAL)
	{
		temp = branch->l;
		branch->l = new_node(leaf);
		branch->l->l = temp;
		return (1);
	}
	if (!branch->r)
	{
		branch->r = new_node(leaf);
		return (1);
	}
	if (branch->r && leaf.type != VAL)
	{
		temp = branch->r;
		branch->r = new_node(leaf);
		branch->r->r = temp;
		return (1);
	}
	return (0);
}

void free_tree(b_tree *tree)
{
	if (!tree)
		return;
	free_tree(tree->l);
	free_tree(tree->r);
	free(tree);
}