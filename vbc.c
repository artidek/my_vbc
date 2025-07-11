#include "vbc.h"

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

void parse_input(b_tree **tree, char *parse_str)
{
	int		i = 0;
	b_tree	node;
	while (parse_str[i])
	{
		if (isdigit(parse_str[i]))
		{
			node = (b_tree){.type = VAL, .val = parse_str[i] - 48, .l = NULL,
				.r = NULL};
			push_tree(tree, node);
		}
		else if (parse_str[i] == '+' && parse_str[i + 1])
		{
			node = (b_tree){.type = ADD, .l = NULL, .r = NULL};
			pop_tree(tree, node);
		}
		else if (parse_str[i] == '*' && parse_str[i + 1])
		{
			node = (b_tree){.type = MULT, .l = NULL, .r = NULL};
			push_tree(tree, node);
		}
		else if (parse_str[i] == '(')
		{
			char *str = build_str(parse_str , &i);
			int temp = 0;
			node = (b_tree){.type = VAL, .val = parse_bracket(str, &temp), .l = NULL,
				.r = NULL};
			push_tree(tree, node);
			free(str);
		}
		if (parse_str[i])
			i++;
	}
}

int	main(int argc, char **argv)
{
	char	*parse_str;
	b_tree	*tree;
	b_tree	*temp;

	if (argc < 2)
		return (1);
	parse_str = argv[1];
	tree = NULL;
	parse_input(&tree, argv[1]);
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
