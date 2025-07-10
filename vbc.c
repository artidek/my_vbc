#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

b_tree	*new_node(b_tree node)
{
	b_tree	*new_node;

	new_node = calloc(sizeof(node), 1);
	if (!new_node)
		return (NULL);
	*new_node = node;
	return (new_node);
}

int	add_leaf(b_tree *branch, b_tree leaf)
{
	b_tree	*temp;

	if (!branch->l)
	{
		branch = new_node(leaf);
		return (1);
	}
	else if (branch->l && leaf.type != VAL)
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
	else if (branch->r && leaf.type != VAL)
	{
		temp = branch->r;
		branch->r = new_node(leaf);
		branch->r->r = temp;
		return (1);
	}
	return (0);
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

int	traverse_tree(b_tree *tree)
{
	switch (tree->type)
	{
	case ADD:
		return (traverse_tree(tree->l) + traverse_tree(tree->r));
		break ;
	case MULT:
		return (traverse_tree(tree->l) * traverse_tree(tree->r));
		break ;
	case VAL:
		return (tree->val);
		break ;
	default:
		break ;
	}
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
		temp->l = new_node(node);
		return ;
	}
	if (!temp->r)
	{
		temp->r = new_node(node);
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

void after_brace(char *str, int *j, int *i, b_tree **tree)
{
	b_tree	node;
	if (str[*j + 1])
	{
		if (str[*j + 1] == '+')
		{
			node = (b_tree){.type = ADD, .l = NULL, .r = NULL};
			pop_tree(tree, node);
			(*j)++;
			(*i)+=2;
		}
		else if (str[*j + 1] == '*')
		{
			node = (b_tree){.type = MULT, .l = NULL, .r = NULL};
			pop_tree(tree, node);
			(*j)++;
			(*i)+=2;
		}
	}
}

void	parse_brace(char *str, int *i, b_tree **tree)
{
	int		j;
	int		count_open;
	int		count_close;
	b_tree	node;

	j = 0;
	count_open = 0;
	count_close = 0;
	while (str[j])
	{
		if (str[j] == '(')
			count_open++;
		if (str[j] == ')')
			break ;
		j++;
	}
	j = 0;
	while (count_close != count_open)
	{
		if (str[j] != '(' || str[j] != ')')
		{
			if (isdigit(str[j]))
			{
				node = (b_tree){.type = VAL, .val = str[j] - 48, .l = NULL,
					.r = NULL};
				push_tree(tree, node);
			}
			else if (str[j] == '+')
			{
				node = (b_tree){.type = ADD, .l = NULL, .r = NULL};
				push_tree(tree, node);
			}
			else if (str[j] == '*')
			{
				node = (b_tree){.type = MULT, .l = NULL, .r = NULL};
				push_tree(tree, node);
			}
		}
		if (str[j] == ')')
		{
			after_brace(&str[j], &j, i, tree);
			count_close++;
		}
		if (count_close != count_open)
		{
			j++;
			(*i)++;
		}
		printf("str[j] %c\n", str[j]);
	}
}

int	main(int argc, char **argv)
{
	int		i;
	char	*parse_str;
	b_tree	node;
	b_tree	*tree;
	b_tree	*temp;

	if (argc < 2)
		return (1);
	i = 0;
	parse_str = argv[1];
	tree = NULL;
	while (parse_str[i])
	{
		if (isdigit(parse_str[i]))
		{
			node = (b_tree){.type = VAL, .val = parse_str[i] - 48, .l = NULL,
				.r = NULL};
			push_tree(&tree, node);
		}
		else if (parse_str[i] == '+')
		{
			node = (b_tree){.type = ADD, .l = NULL, .r = NULL};
			pop_tree(&tree, node);
		}
		else if (parse_str[i] == '*')
		{
			node = (b_tree){.type = MULT, .l = NULL, .r = NULL};
			push_tree(&tree, node);
		}
		else if (parse_str[i] == '(')
			parse_brace(&parse_str[i], &i, &tree);
		i++;
	}
	temp = tree;
	// while (temp->l)
	// {
	// 	printf("   %p\n", temp);
	// 	printf("left %p      ", temp->l);
	// 	printf("right %p\n", temp->r);
	// 	temp = temp->l;
	// }
	// temp = tree;
	// while (temp->r)
	// {
	// 	printf("   %p\n", temp);
	// 	printf("left %p      ", temp->l);
	// 	printf("right %p\n", temp->r);
	// 	temp = temp->r;
	// }
	printf("result: %d\n", traverse_tree(tree));
	return (0);
}
