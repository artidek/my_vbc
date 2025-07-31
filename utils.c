/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:08:13 by aobshatk          #+#    #+#             */
/*   Updated: 2025/07/31 16:17:39 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vbc.h"

b_tree	*parse_bracket(char *str, int *i, b_tree *tree)
{
	b_tree *temp = tree;
	while (str[*i])
	{
		if (str[*i] == '(')
		{
			(*i)++;
			temp = parse_bracket(str, i, tree);
			int res = traverse_tree(temp);
			free_tree(temp);
			push_tree(&tree, (b_tree){.type = VAL, .val = res, .l = NULL, .r = NULL});
		}
		if (isdigit(str[*i]))
			push_tree(&tree, (b_tree){.type = VAL, .val = str[*i] -48, .l = NULL, .r = NULL});
		else if (str[*i] == '+')
		{
			pop_tree(&tree, (b_tree){.type = ADD, .l = NULL, .r = NULL});
		}
		else if (str[*i] == '*')
			push_tree(&tree, (b_tree){.type = MULT, .l = NULL, .r = NULL});
		else if (str[*i] == ')')
		{
			return tree;
		}
		(*i)++;
	}
	return NULL;
}
