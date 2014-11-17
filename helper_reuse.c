/*
** helper_reuse.c for Bistromatique in /home/barrau_h/Desktop/calc
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Tue Nov 11 23:57:58 2014 Hippolyte Barraud
** Last update Sat Nov 15 03:14:06 2014 Hippolyte Barraud
*/

#include"include/bistromatique.h"

void	push_fatnum_reuse(t_root *stacks, t_fatnum *num)
{
  stacks->reuse_stack[stacks->index_reuse++] = num;
}

t_fatnum	*pop_fatnum_reuse(t_root *stacks)
{
  return (stacks->reuse_stack[--stacks->index_reuse]);
}

/*
** Instead of simply freeing the two fatnum operands at each operation and
** therefore mallocing some more later, the program implements reuse feature.
** When it become useless, a fatnum instance is stored onto a reuse stack.
*/
void register_for_reuse(t_root *stacks, t_fatnum *num)
{
  push_fatnum_reuse(stacks, num);
}

/*
** When the program needs a new fatnum to work on, this function is called.
** It check for the availibility of fatnums on the stack and if so, give it.
** This allowed HUGE performance gain to this frankly slow program.
*/
t_fatnum *get_fatnum(t_root *stacks)
{
  if (stacks->index_reuse > 0)
    return (pop_fatnum_reuse(stacks));
  else
    return ((void*)malloc_or_die(sizeof(t_fatnum)));
}

/*
** This function is called at the very end of the session. It free all the
** items present on the fatnum stack. It does not check for others because we
** know for shure they have been.
*/
void clear_stacks(t_root *stacks)
{
  int i;

  i = 0;
  while (stacks->fatnum_stack[i] != NULL)
    free(stacks->fatnum_stack[i++]);
}
