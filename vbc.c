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
	return (tree->val);
}

void parse_input(b_tree **tree, char *parse_str)
{
	int		i = 0;

	while (parse_str[i])
	{
		if (isdigit(parse_str[i]))
		{
			push_tree(tree, (b_tree){.type = VAL, .val = parse_str[i] - 48, .l = NULL,
				.r = NULL});
			i++;
		}
		else if (parse_str[i] == '+')
		{
			pop_tree(tree, (b_tree){.type = ADD, .l = NULL, .r = NULL});
			i++;
		}
		else if (parse_str[i] == '*')
		{
			push_tree(tree, (b_tree){.type = MULT, .l = NULL, .r = NULL});
			i++;
		}
		else if (parse_str[i] == '(')
		{
			push_tree(tree, (b_tree){.type = VAL,.val = parse_bracket(parse_str, &i, NULL, 0), .l = NULL, .r = NULL});
		}
	}
}

int	main(int argc, char **argv)
{
	b_tree	*tree;

	if (argc < 2)
		return (1);
	tree = NULL;
	if (error_check(argv[1]))
		return 1;
	parse_input(&tree, argv[1]);
	printf("result: %d\n", traverse_tree(tree));
	free_tree(tree);
	return (0);
}
