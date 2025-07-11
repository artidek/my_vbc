/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:08:13 by aobshatk          #+#    #+#             */
/*   Updated: 2025/07/11 23:42:37 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vbc.h"

int	parse_bracket(char *str, int *i)
{
	b_tree *tree = NULL;
	b_tree node;

	while (str[*i])
	{
		if (str[*i] == ')')
		{
			int val = traverse_tree(tree);
			printf("i %d\n", val);
			(*i)++;
			return (val);
		}
		if (str[*i] == '(')
		{
			(*i)++;
			node = (b_tree){.type = VAL, .val = parse_bracket(str, i), .l = NULL,
				.r = NULL};
			push_tree(&tree, node);
		}
		else if (isdigit(str[*i]))
		{
			node = (b_tree){.type = VAL, .val = str[*i] - 48, .l = NULL,
				.r = NULL};
			push_tree(&tree, node);
		}
		else if (str[*i] == '+' && str[*i + 1])
		{
			node = (b_tree){.type = ADD, .l = NULL, .r = NULL};
			pop_tree(&tree, node);
		}
		else if (str[*i] == '*' && str[*i + 1])
		{
			node = (b_tree){.type = MULT, .l = NULL, .r = NULL};
			push_tree(&tree, node);
		}
		if (str[*i])
			(*i)++;
	}
	return (traverse_tree(tree));
}

char	*build_str(char *str, int *i)
{
	int open_cnt = 0;
	int close_cnt = 0;
	t_list *list = NULL;

	while (str[*i])
	{
		if (str[*i] == '(')
			open_cnt++;
		if (str[*i] == ')')
			close_cnt++;
		add_node(&list, new_nd(str[*i]));
		if (open_cnt == close_cnt)
		{
			(*i)++;
			break ;
		}
		(*i)++;
	}
	int size = list_size(list);
	char *res = malloc(sizeof(char) * size + 1);
	t_list *temp = list;
	int j = 0;
	while (temp)
	{
		res[j] = temp->val;
		j++;
		temp = temp->next;
	}
	free_list(&list);
	res[size] = 0;
	return (res);
}