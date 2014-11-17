/*
** main.c for Bistromatique in /home/barrau_h/Desktop/Bistromatique FINAL/Bistromatique
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sun Nov  9 04:35:25 2014 Hippolyte Barraud
** Last update Sat Nov 15 03:02:53 2014 Hippolyte Barraud
*/

#include"include/bistromatique.h"

t_root root;
t_root *stacks = &root;
t_fatnum n1;
t_fatnum n2;

/*
** Handles parenthesis according to shutting yard method. If ')' is sent,
** evaluates all the operators until the '(' is reached. Else, push the
** operator onto the relevent stack.
*/
int	treat_parenthesis(t_op *op, t_op *pop)
{
  if (op->op == '(')
    {
      push_operator(op, stacks);
      return (1);
    }
  else if (op->op == ')')
    {
      while (stacks->index_operator_stack>0 && stacks->
	     operator_stack[stacks->index_operator_stack - 1]->op != '(')
	process_postscript(&n1, &n2, pop, stacks);
      pop = pop_operator(stacks);
      return (1);
    }
  return (0);
}

/*
** Function that handles operators according to the shutting yard algorithm.
** If possible, evaluates what can be evaluated. Or else, push the
** operator onto the stack for later use.
*/
void	treat_operator(register t_op *op)
{
  t_op	*pop;

  pop = NULL;
  if (treat_parenthesis(op, pop) == 1)
    return;
  if (op->assoc == BINDTYPE_RIGHT)
    while (stacks->index_operator_stack && op->prec <
	   stacks->operator_stack[stacks->index_operator_stack - 1]->prec)
      process_postscript(&n1, &n2, pop, stacks);
  else
    while (stacks->index_operator_stack && op->prec <=
	   stacks->operator_stack[stacks->index_operator_stack - 1]->prec)
      process_postscript(&n1, &n2, pop, stacks);
  push_operator(op, stacks);
}

/*
** Handles fatnum representation in the input string
*/
void	treat_fatnum(register char *expr)
{
  if (my_isspace(*expr, stacks->base))
    {
      push_fatnum(init_fatnum_with_val
		  (stacks->check_start, get_fatnum(stacks), stacks->base),
		  stacks);
      stacks->check_start = NULL;
      stacks->last_operator = NULL;
    }
  else if ((stacks->op = getop(*expr)))
    {
      push_fatnum(init_fatnum_with_val
		  (stacks->check_start, get_fatnum(stacks),
		   stacks->base), stacks);
      stacks->check_start = NULL;
      treat_operator(stacks->op);
      stacks->last_operator = stacks->op;
    }
  else if (!my_isdigit(*expr, stacks->base))
    print_fatal_error(6);
}

/*
** Root function; home of the actual shutting yard process. This function
** iterates through all the characters of the input, convert it to postfix
** notation using stacks (one for the operators and another for the numbers),
** and finally evaluate the RPN expression. Note that a third stack is used to
** store useless fatnums (operands of past operations) for reuse purpose.
** This allowed the programm to perform better (less memory to initialize).
*/
void	shutting_yard(register char *expr)
{
  if (!stacks->check_start)
    {
      if ((stacks->op = getop(*expr)))
	{
	  if (stacks->last_operator &&
	      (stacks->last_operator == &stacks->start_operator ||
	       stacks->last_operator->op != ')'))
	    if (stacks->op->op == '-')
	      stacks->op = getop('_');
	    else if (stacks->op->op == '+')
	      stacks->op = getop('$');
	    else if (stacks->op->op != '(')
	      print_fatal_error(6);
	  treat_operator(stacks->op);
	  stacks->last_operator = stacks->op;
	}
      else if (my_isdigit(*expr, stacks->base))
	stacks->check_start = expr;
      else if (!my_isspace(*expr, stacks->base))
	print_fatal_error(6);
    }
  else
    treat_fatnum(expr);
}

/*
** Enry point of the algorithm. Include a progress bar display for enormus
** expressions. This feature have the drawback of breaking the use of
** redirecting this program's output to another program via a pipe.
** For compatibility reason, add a fith parameter '-p' to enable it.
** The use of the system call "fflush" is necessary for a proper progress bar,
** they can be safely delete without breaking the program at all.
*/
int	eval_expr(char *base, char *operators, register char *expr,
		  int size_loc, int p)
{
  float i;
  int last_i;

  i = 0;
  last_i = -1;
  init(stacks, base);
  convert_to_inner_op(expr, operators);
  stacks->operator_list = operators;
  while (*expr)
    {
      print_progress(i + 1, size_loc, &last_i, ((i / size_loc) * 100), p);
      shutting_yard(expr);
      expr++;
      last_i = ((i++ / size_loc) * 100);
    }
  fflush(0);
  printf("\33[2K\r");
  fflush(0);
  if (stacks->check_start)
    push_fatnum(init_fatnum_with_val(stacks->check_start,
				     get_fatnum(stacks), stacks->base), stacks);
  while (stacks->index_operator_stack)
    process_postscript(&n1, &n2, stacks->op, stacks);
  print_t_fatnum(from_decimal_to_base(stacks->fatnum_stack[0], base,
		  get_fatnum(stacks)), operators);
  clear_stacks(stacks);
}
