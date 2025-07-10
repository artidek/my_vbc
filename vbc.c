#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct s_b_tree
{
	enum {ADD, MULT, VAL} type;
	int val;
	struct s_b_tree *l;
	struct s_b_tree *r;
} b_tree;

b_tree *new_node(b_tree node)
{
	b_tree *new_node = calloc(sizeof(node), 1);
	if (!new_node)
		return (NULL);
	*new_node = node;
	return (new_node);
}

void pop_tree(b_tree **tree, b_tree node)
{
	if (!*tree)
	{
		*tree = new_node(node);
		return;
	}
	b_tree *temp = *tree;
	if (temp->type == VAL || temp->type == MULT)
	{
		*tree = new_node(node);
		(*tree)->l = temp;
	}
	else
	{
		*tree = new_node(node);
		(*tree)->r = temp;
	}
}

int traverse_tree (b_tree *tree)
{
	if (tree)
	{
		switch (tree->type)
		{
			case ADD:
				return (traverse_tree(tree->l) + traverse_tree(tree->r));
				break;
			case MULT:
				return (traverse_tree(tree->l) * traverse_tree(tree->r));
				break;
			case VAL:
				return (tree->val);
				break;
			default:
				break;
		}
	}
	return (0);
}

void push_tree(b_tree **tree, b_tree node)
{
	if (!*tree)
	{
		*tree = new_node(node);
		return;
	}
	b_tree *temp = *tree;
	if (node.type == VAL)
	{
		if (temp->l && temp->l->type != VAL)
		{
			while(temp->l && temp->l->type != VAL)
				temp = temp->l;
			if (!temp->l)
			{
				temp->l = new_node(node);
			}
			else
				temp->r = new_node(node);
			return;
		}
		if (temp->r && temp->r->type != VAL)
		{
			while(temp->r && temp->r->type != VAL)
				temp = temp->r;
			if (!temp->r)
			{
				temp->r = new_node(node);
			}
			else
				temp->l = new_node(node);
		}
	}
	else
	{
		if (temp->r)
		{
			while (temp->r && temp->r->type != VAL)
				temp = temp->r;
			while (temp->l && temp->l->type != VAL)
				temp = temp->l;
			if (!temp->l)
			{
				temp->l = new_node(node);
			}
			else
			{
				b_tree *l_temp = temp->l;
				temp->l = new_node(node);
				temp->l->l = l_temp;
			}
		}
		else if (temp->type == VAL)
		{
			*tree = new_node(node);
			(*tree)->l = temp;
		}
		else if (!temp->l)
		{
			temp->l = new_node(node);
		}
		else if (temp->l)
		{
			while (temp->l && temp->l->type != VAL)
				temp = temp->l;
			if (!temp->l)
			{
				temp->l = new_node(node);
			}
			else
			{
				b_tree *l_temp = temp->l;
				temp->l = new_node(node);
				temp->l->l = l_temp;
			}
		}
	}
}

int main (int argc, char **argv)
{
	if (argc < 2)
		return (1);
	int i = 0;
	char *parse_str = argv[1];
	b_tree node;
	b_tree *tree = NULL;
	while (parse_str[i])
	{
		if (isdigit(parse_str[i]))
		{
			node = (b_tree){.type = VAL, .val = parse_str[i] - 48, .l = NULL, .r = NULL};
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
		i++;
	}
	// while (tree->r)
	// {
	// 	printf("   %d\n", tree->type);
	// 	if (tree->l)
	// 		printf ("left %d      ", tree->l->type);
	// 	if (tree->r)
	// 		printf("right %d\n", tree->r->type);
	// 	tree = tree->r;
	// }
	printf("result: %d\n", traverse_tree(tree));
	return (0);
}
