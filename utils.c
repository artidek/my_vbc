/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:08:13 by aobshatk          #+#    #+#             */
/*   Updated: 2025/08/01 12:03:55 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vbc.h"

b_tree	*parse_bracket(char *str, int *i, b_tree *tree, int count)
{
	if (str[*i] == '(')
	{
		(*i)++;
		return (parse_bracket(str, i, tree, count += 1));
	}
	while (str[*i] && count > 0)
	{
		if (str[*i] == '(')
	{
		(*i)++;
		return (parse_bracket(str, i, tree, count += 1));
	}
		if (isdigit(str[*i]))
			push_tree(&tree, (b_tree){.type = VAL, .val = str[*i] -48, .l = NULL, .r = NULL});
		else if (str[*i] == '+')
		{
			if (count == 1)
				pop_tree(&tree, (b_tree){.type = ADD, .l = NULL, .r = NULL});
			if (count >= 2)
				push_tree(&tree, (b_tree){.type = ADD, .l = NULL, .r = NULL});
		}
		else if (str[*i] == '*')
			push_tree(&tree, (b_tree){.type = MULT, .l = NULL, .r = NULL});
		else if (str[*i] == ')')
		{
			(*i)++;
			return (parse_bracket(str, i, tree, count -= 1));
		}
		(*i)++;
	}
	return (tree);
}
