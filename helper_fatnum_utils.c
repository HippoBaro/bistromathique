/*
** helper_fatnum_utils.c for Bistromatique in /home/barrau_h/Desktop/Bistromatique FINAL/Bistromatique
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sun Nov  9 04:23:18 2014 Hippolyte Barraud
** Last update Sat Nov 15 02:38:39 2014 Hippolyte Barraud
*/

#include"include/bistromatique.h"

/*
** Compare two fatnum.
*/
int	fatnum_cmp(t_fatnum *a, t_fatnum *b)
{
  register int	i;

  if ((a->signbit == MINUS) && (b->signbit == PLUS))
    return (PLUS);
  if ((a->signbit == PLUS) && (b->signbit == MINUS))
    return (MINUS);
  if (b->len > a->len)
    return (PLUS * a->signbit);
  if (a->len > b->len)
    return (MINUS * a->signbit);
  i = a->len;
  while (i >= 0)
    {
      if (a->digits[i] > b->digits[i])
	return (MINUS * a->signbit);
      if (b->digits[i] > a->digits[i])
	return (PLUS * a->signbit);
      i--;
    }
  return (0);
}

/*
** Helper function. Called at the end of each operation on the result.
** Format the fatnum to avoid zeros at the begining of the number.
** Ex : 00042 returns 42.
*/
void	format_fatnum(t_fatnum *n)
{
  while ((n->len > 0) && (n->digits[n->len] == 0))
    n->len--;
  if ((n->len == 0) && (n->digits[0] == 0))
    n->signbit = PLUS;
}

/*
** Shift every digit to the left d-times.
** Ex : for n = 42 & d = 2 -> 4200
*/
void	digit_shift(t_fatnum *n, int d)
{
  int	i;

  if ((n->len == 0) && (n->digits[0] == 0))
    return;
  i = n->len;
  while (i >= 0)
    {
      n->digits[i + d] = n->digits[i];
      i--;
    }
  i = 0;
  while (i < d)
    {
      n->digits[i] = 0;
      i++;
    }
  n->len = n->len + d;
}

/*
** Heper function. Duplicate a fatnum.
*/
t_fatnum	*fatnum_dup(t_fatnum *src, t_fatnum *dest)
{
  register int		i;

  i = 0;
  init_fatnum(dest);
  while (i <= src->len)
    {
      dest->digits[i] = src->digits[i];
      i++;
    }
  dest->len = src->len;
  dest->signbit = src->signbit;
  return (dest);
}

/*
** Heper function. Retuns 1 if num == zero orelse retun 0.
*/
inline int	is_fatnum_zero(t_fatnum *num)
{
  if (num->len == 0 && num->digits[0] == 0)
    return (1);
  return (0);
}
