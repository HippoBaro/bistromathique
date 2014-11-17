/*
** miscs.c for Bistromatique in /home/barrau_h/Desktop/Bistromatique FINAL/Bistromatique
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sun Nov  9 04:30:29 2014 Hippolyte Barraud
** Last update Sat Nov 15 03:15:54 2014 Hippolyte Barraud
*/

#include "include/bistromatique.h"

static struct  s_op ops[] = {
  { '(', 0, BINDTYPE_NONE, 0, NULL },
  { ')', 0, BINDTYPE_NONE, 0, NULL },
  { '+', 5, BINDTYPE_LEFT, 0, &add },
  { '-', 5, BINDTYPE_LEFT, 0, &subtract },
  { '*', 8, BINDTYPE_LEFT, 0, &multiply },
  { '/', 8, BINDTYPE_LEFT, 0, &divide },
  { '%', 8, BINDTYPE_LEFT, 0, &mod },
  { '_', 10, BINDTYPE_RIGHT, 1, &unary_minus },
  { '$', 10, BINDTYPE_RIGHT, 1, &unary_abs }
};

int	my_max(int a, int b)
{
  if (a > b)
    return (a);
  else
    return (b);
}

/*
** Helper function, initialize a default value for start_operator
** (start_operator MUST NOT be NULL at startup).
** The operator 'X' does not exit, but it doesn't matter since it wil be
** overwritten later.
*/
void	init(t_root *stacks, char *base)
{
  stacks->start_operator.op = 'X';
  stacks->start_operator.prec = 0;
  stacks->start_operator.assoc = BINDTYPE_NONE;
  stacks->start_operator.unary = 0;
  stacks->start_operator.eval = NULL;
  stacks->last_operator = &stacks->start_operator;
  stacks->base = base;
}

/*
** The internal mechanism of the application only support standard operators.
** Thus, we first "convert" the user input into those before any parsing.
** WARNING : Even if a custom operator set is set, a expression like "2+2" WILL
** work, even if + is not part of the custom operators.
*/
int convert_to_inner_op(char *expr, char *cus_op)
{
  register int i;
  register int b;

  if (strcmp(cus_op,  "()+-*/%") == 0)
    return (0);
  i = 0;
  while (expr[i] != '\0')
    {
      b = 0;
      while (b < 7)
	{
	  if (expr[i] == cus_op[b])
	    expr[i] = ops[b].op;
	  b++;
	}
      i++;
    }
    return (0);
}

/*
** Return the operator's informations based on passed char.
*/
t_op	*getop(char ch)
{
  register int	i;

  i = 0;
  while (i < sizeof ops / sizeof ops[0])
    {
      if (ops[i].op == ch)
	return (ops + i);
      i++;
    }
  return (NULL);
}

/*
** Helper function. Concatenate two strings.
*/
char *my_strcat(char *dest, char *src)
{
  register int i;
  register int j;

  i = 0;
  j = 0;
  while (dest[i] != '\0')
    i++;
  while (src[j] != '\0')
    dest[i + j] = src[j++];
  dest[i + j] = '\0';
  return dest;
}
