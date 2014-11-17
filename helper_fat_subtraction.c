/*
** helper_fat_subtraction.c for Bistromatique in /home/barrau_h/Desktop/Bistromatique FINAL/Bistromatique
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sun Nov  9 04:19:12 2014 Hippolyte Barraud
** Last update Sat Nov 15 03:15:31 2014 Hippolyte Barraud
*/

#include"include/bistromatique.h"

/*
** Helper function. Handle the sign for the subtraction (converting it to an
** addition if necessary).
** Helps comply with the norm.
*/
inline int	subtract_treatsign(t_fatnum *a, t_fatnum *b, t_fatnum *c)
{
  if ((a->signbit == MINUS) || (b->signbit == MINUS))
    {
      b->signbit = -1 * b->signbit;
      add(a, b, c);
      b->signbit = -1 * b->signbit;
      return (1);
    }
  if (fatnum_cmp(a, b) == PLUS)
    {
      subtract(b, a, c);
      c->signbit = MINUS;
      return (1);
    }
  return (0);
}

/*
** Schoolbook subtraction.
*/
t_fatnum	*subtract(t_fatnum *a, t_fatnum *b, t_fatnum *c)
{
  register int		borrow;
  register int		v;
  register int		i;

  init_fatnum(c);
  if (subtract_treatsign(a, b, c) == 1)
    return (c);
  c->len = my_max(a->len, b->len);
  borrow = 0;
  i = 0;
  while (i <= (c->len))
    {
      v = (a->digits[i] - borrow - b->digits[i]);
      if (a->digits[i] > 0)
	borrow = 0;
      if (v < 0)
	{
	  v = v + 10;
	  borrow = 1;
	}
      c->digits[i] = (char)v % 10;
      i++;
    }
  format_fatnum(c);
  return (c);
}
