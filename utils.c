/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:08:13 by aobshatk          #+#    #+#             */
/*   Updated: 2025/07/12 13:47:37 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vbc.h"

int	parse_bracket(char *str, int *i)
{
	b_tree	*outer = NULL;
	b_tree	*inner = NULL;
	b_tree	node;

	while (str[*i])
	{
		if (str[*i] == '(')
		{
			while (str[*i] == '(')
				(*i)++;
			parse_expr(&inner, str, i);
			node = (b_tree){.type = VAL, .val = traverse_tree(inner), .l = NULL,
				.r = NULL};
			push_tree(&outer, node);
			free_tree(inner);
			inner = NULL;
		}
		if (isdigit(str[*i]))
		{
			node = (b_tree){.type = VAL, .val = str[*i] - 48, .l = NULL,
				.r = NULL};
			push_tree(&outer, node);
		}
		else if (str[*i] == '+')
		{
			node = (b_tree){.type = ADD, .l = NULL, .r = NULL};
			pop_tree(&outer, node);
		}
		else if (str[*i] == '*')
		{
			node = (b_tree){.type = MULT, .l = NULL, .r = NULL};
			push_tree(&outer, node);
		}
		if (str[*i] == ')')
		{
			int val = traverse_tree(outer);
			free_tree(outer);
			return (val);
		}
		if (str[*i])
			(*i)++;
	}
	return (0);
}

void	parse_expr(b_tree **tree, char *str, int *i)
{
	b_tree node;

	while (str[*i])
	{
		if (isdigit(str[*i]))
		{
			node = (b_tree){.type = VAL, .val = str[*i] - 48, .l = NULL,
				.r = NULL};
			push_tree(tree, node);
		}
		else if (str[*i] == '+')
		{
			node = (b_tree){.type = ADD, .l = NULL, .r = NULL};
			pop_tree(tree, node);
		}
		else if (str[*i] == '*')
		{
			node = (b_tree){.type = MULT, .l = NULL, .r = NULL};
			push_tree(tree, node);
		}
		else if (str[*i] == ')')
		{
			(*i)++;
			return;
		}
		if (str[*i])
			(*i)++;
	}
}