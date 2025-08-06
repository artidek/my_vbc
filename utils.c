/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:08:13 by aobshatk          #+#    #+#             */
/*   Updated: 2025/08/06 18:43:30 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vbc.h"

int parse_bracket(char *str, int *i, b_tree *tree, int count)
{
	int res = 0;

	if (count == 0)
	{
		if (str[*i] && str[*i] == '(')
		{
			(*i)++;
			res = parse_bracket(str, i, NULL, count + 1);
			free_tree(tree);
			tree = NULL;
			push_tree(&tree, (b_tree){.type = VAL, .val = res, .l = NULL, .r = NULL});
			count--;
		}
	}
	while (count > 0)
	{
		if (str[*i] && str[*i] == '(')
		{
			(*i)++;
			res = parse_bracket(str, i, NULL, count + 1);
			push_tree(&tree, (b_tree){.type = VAL, .val = res, .l = NULL, .r = NULL});
		}
		if (isdigit(str[*i]))
		{
			push_tree(&tree, (b_tree){.type = VAL, .val = str[*i] - 48, .l = NULL,
				.r = NULL});
		}
		else if (str[*i] == '+')
		{
			pop_tree(&tree, (b_tree){.type = ADD, .l = NULL, .r = NULL});
		}
		else if (str[*i] == '*')
		{
			push_tree(&tree, (b_tree){.type = MULT, .l = NULL, .r = NULL});
		}
		else if (str[*i] == ')')
		{
			(*i)++;
			count--;
			res = traverse_tree(tree);
			free_tree(tree);
			tree = NULL;
			return (res);
		}
		(*i)++;
	}
	if (tree)
	{
		res = traverse_tree(tree);
		free_tree(tree);
	}
	return (res);	
}
