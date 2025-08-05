/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:08:13 by aobshatk          #+#    #+#             */
/*   Updated: 2025/08/05 23:23:50 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vbc.h"

int	parse_bracket(char *str, int *i, b_tree *tree, int count)
{
	int	res;

	res = 0;
	if (str[*i] == '(' && count == 0)
	{
		(*i)++;
		res = parse_bracket(str, i, tree, count + 1);
		push_tree(&tree, (b_tree){.type = VAL, .val = res, .l = NULL, .r = NULL});
		count -= 1;
	}
	if (str[*i] == '(' && count > 0)
	{
		printf ("str %c\n", str[*i]);
		(*i)++;
		res = parse_bracket(str, i, NULL, count + 1);
		push_tree(&tree, (b_tree){.type = VAL, .val = res, .l = NULL, .r = NULL});
		parse_bracket(str, i , tree, count - 1);
	}
	if (count == 0)
		return res;
	if (str[*i] == '(')
	{
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
		res = traverse_tree(tree);
		free_tree(tree);
		return (res);
	}
	return (res);
}
