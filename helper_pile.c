/*
** helper_pile.c for Bistromatique in /home/barrau_h/Desktop/Bistromatique FINAL/Bistromatique
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sun Nov  9 04:20:35 2014 Hippolyte Barraud
** Last update Sat Nov 15 02:31:06 2014 Hippolyte Barraud
*/

#include"include/bistromatique.h"

/*
** Helper functions. Basic stacks management functions.
*/
inline void	push_operator(t_op *op, t_root *stacks)
{
  stacks->operator_stack[stacks->index_operator_stack++] = op;
}

inline t_op	*pop_operator(t_root *stacks)
{
  return (stacks->operator_stack[--stacks->index_operator_stack]);
}

/*
** Helper functions. Basic stacks management functions.
** Note that we register the previously allocated memory for later reuse.
*/
inline void	push_fatnum(t_fatnum *num, t_root *stacks)
{
  if (stacks->fatnum_stack[stacks->index_fatnum_stack] != NULL)
    register_for_reuse(stacks,
		       stacks->fatnum_stack[stacks->index_fatnum_stack]);
  stacks->fatnum_stack[stacks->index_fatnum_stack++] = num;
}

inline t_fatnum	*pop_fatnum(t_root *stacks)
{
  return (stacks->fatnum_stack[--stacks->index_fatnum_stack]);
}

/*
** Function that pop an operator and both of it's operands (if needed) and
** push the result onto the stack.
** Note that his function implement a security feature that handles errors. If
** the operator that was poped does not implement an evaluation function (most
** likely a parenthesis), then we can assume that the user's input is
** incorrect. Also, for non-unary operators, check if neither of n1 or n2 is
** NULL, if so there is an error in the input.
*/
inline void	process_postscript(t_fatnum *n1, t_fatnum *n2, t_op *pop,
			   t_root *stacks)
{
  pop = pop_operator(stacks);
  n1 = pop_fatnum(stacks);
  if (pop->unary)
    push_fatnum(pop->eval(n1, NULL, get_fatnum(stacks)), stacks);
  else if (pop->eval != NULL)
    {
	  n2 = pop_fatnum(stacks);
      if (n2 == NULL || n1 == NULL)
    	  print_fatal_error(6);
      push_fatnum(pop->eval(n2, n1, get_fatnum(stacks)), stacks);
    }
  else
    print_fatal_error(6);
  return;
}
