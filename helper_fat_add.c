/*
** helper_fat_add.c for Bistromatique in /home/barrau_h/Desktop/Bistromatique FINAL/Bistromatique
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sun Nov  9 04:26:12 2014 Hippolyte Barraud
** Last update Sat Nov 15 02:33:17 2014 Hippolyte Barraud
*/

#include"include/bistromatique.h"

/*
** Helper function. Handle sign during addition (transform in subtraction if
** necessary).
*/
inline int	add_treatsign(t_fatnum *a, t_fatnum *b, t_fatnum *c)
{
  if (a->signbit == b->signbit)
    c->signbit = a->signbit;
  else
    {
      if (a->signbit == MINUS) {
	a->signbit = PLUS;
	subtract(b, a, c);
	a->signbit = MINUS;
      }
      else {
	b->signbit = PLUS;
	subtract(a, b, c);
	b->signbit = MINUS;
      }
      return (1);
    }
  return (0);
}

/*
** Schoolbook addition.
*/
inline t_fatnum	*add(t_fatnum *a, t_fatnum *b, t_fatnum *c)
{
  register int		carry;
  register int		i;

  init_fatnum(c);
  if (add_treatsign(a, b, c) == 1)
    return (c);
  c->len = my_max(a->len, b->len) + 1;
  carry = 0;
  i = 0;
  while (i <= (c->len))
    {
      c->digits[i] = (char)(carry + a->digits[i] + b->digits[i]) % 10;
      carry = (carry + a->digits[i] + b->digits[i]) / 10;
      i++;
    }
  format_fatnum(c);
  return (c);
}
