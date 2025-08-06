/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:22:25 by aobshatk          #+#    #+#             */
/*   Updated: 2025/08/06 13:36:34 by aobshatk         ###   ########.fr       */
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
void free_tree(b_tree *tree);
int	add_leaf(b_tree *branch, b_tree leaf);
int	traverse_tree(b_tree *tree);
int parse_bracket(char *str, int *i, b_tree *tree, int count);
b_tree	*new_node(b_tree node);
int error_check(char *str);

#endif
