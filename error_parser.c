#include "vbc.h"

static int invalid_token(char *str, int i, int count)
{
	if (!str[i])
		return (count);
	if (str[i] == '(')
		return (invalid_token(str, i += 1, count+=1));
	if (str[i] == ')')
		return (invalid_token(str, i+=1, count-=1));
	return (invalid_token(str, i+=1, count));
}

int invalid_input(char *str, int i)
{
	if (!str[i])
		return 0;
	if ((!isdigit(str[i]) && str[i] != ')') && !str[i + 1])
	{
		printf("invalid end of input\n");
		return 1;
	}
	if(isdigit(str[i]))
	{
		if (!str[i + 1])
			return (invalid_input(str, i + 1));
		if (str[i + 1] && (str[i + 1] == '+' || str[i + 1] == '*'))
			return (invalid_input(str, i + 1));
		if (str[i + 1] && str[i + 1] == ')')
			return (invalid_input(str, i + 1));
	}
	if (str[i] == '+' || str[i] == '*')
	{
		if (str[i + 1] && str[i + 1] == '(')
			return (invalid_input(str, i + 1));
		if (str[i + 1] && isdigit(str[i + 1]))
			return (invalid_input(str, i + 1));
	}
	if (str[i] == '(' || str[i] == ')')
		return (invalid_input(str, i + 1));
	printf("invalide token '%c'\n", str[i + 1]);
	return 1;
}

int error_check(char *str)
{
	if (invalid_token(str, 0, 0) > 0)
	{
		printf("invalid token (\n");
		return (1);
	}
	if (invalid_token(str, 0, 0) < 0)
	{
		printf("invalid token )\n");
		return (1);
	}
	if (invalid_input(str, 0))
	{
		return (1);
	}
	return (0);
}