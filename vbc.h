/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:22:25 by aobshatk          #+#    #+#             */
/*   Updated: 2025/07/31 16:05:54 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VBC_H
#define VBC_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct s_b_tree
{
	enum
	{
		ADD,
		MULT,
		VAL
	} type;
	int				val;
	struct s_b_tree	*l;
	struct s_b_tree	*r;
}					b_tree;

void	push_tree(b_tree **tree, b_tree node);
void	pop_tree(b_tree **tree, b_tree node);
void parse_input(b_tree **tree, char *parse_str);
void	parse_expr(b_tree **tree, char *str, int *i);
void free_tree(b_tree *tree);
int	add_leaf(b_tree *branch, b_tree leaf);
int	traverse_tree(b_tree *tree);
b_tree	*parse_bracket(char *str, int *i, b_tree *tree);
char	*build_str(char *str, int *i);
b_tree	*new_node(b_tree node);

#endif
