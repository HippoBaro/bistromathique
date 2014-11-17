/*
** helper_fat_operator.c for Bistromatique in /home/barrau_h/Desktop/Bistromatique FINAL/Bistromatique
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sun Nov  9 04:13:52 2014 Hippolyte Barraud
** Last update Sat Nov 15 02:37:09 2014 Hippolyte Barraud
*/

#include"include/bistromatique.h"

/*
** Schoolbook multiplication. The most time-demanding operations. Could be
** better. There are larges rooms for improvements.
*/
t_fatnum	*multiply(t_fatnum *a, t_fatnum *b, t_fatnum *c)
{
  static t_fatnum	row;
  static t_fatnum	tmp;
  register int		i;
  register int		j;

  init_fatnum(c);
  fatnum_dup(a, &row);
  i = 0;
  while (i <= b->len)
    {
      j = 1;
      while (j <= b->digits[i])
	{
	  add(c, &row, &tmp);
	  fatnum_dup(&tmp, c);
	  j++;
	}
      digit_shift(&row, 1);
      i++;
    }
  c->signbit = a->signbit * b->signbit;
  format_fatnum(c);
  return (c);
}

/*
** Helper function. Helps comply with the norm.
*/
inline t_fatnum	*divide_helper(t_fatnum *a, t_fatnum *b, t_fatnum *c,
			       t_fatnum row, t_fatnum tmp, int asign, int bsign)
{
  register int		i;

  i = a->len;
  while (i >= 0)
    {
      digit_shift(&row, 1);
      row.digits[0] = a->digits[i];
      c->digits[i] = 0;
      while (fatnum_cmp(&row, b) != PLUS)
	{
	  c->digits[i] ++;
	  subtract(&row, b, &tmp);
	  row = tmp;
	}
      i--;
    }
  format_fatnum(c);
  a->signbit = asign;
  b->signbit = bsign;
  return (c);
}

/*
** Schoolbook division, this function only handle signs. See division_helper
** for computation. Proected againts division by zero.
*/
t_fatnum	*divide(t_fatnum *a, t_fatnum *b, t_fatnum *c)
{
  static t_fatnum	row;
  static t_fatnum	tmp;
  int		asign;
  int		bsign;

  if (is_fatnum_zero(b) == 1)
    print_fatal_error(7);
  init_fatnum(c);
  c->signbit = a->signbit * b->signbit;
  asign = a->signbit;
  bsign = b->signbit;
  a->signbit = PLUS;
  b->signbit = PLUS;
  init_fatnum(&row);
  init_fatnum(&tmp);
  c->len = a->len;
  return (divide_helper(a, b, c, row, tmp, asign, bsign));
}

/*
** Finds the modulo with simple maths.
** Protected againts mod by zero.
*/
t_fatnum	*mod(t_fatnum *a, t_fatnum *b, t_fatnum *c)
{
  static t_fatnum	div;
  static t_fatnum	mult;

  if (is_fatnum_zero(b) == 1)
    print_fatal_error(8);
  divide(a, b, &div);
  multiply(&div, b, &mult);
  subtract(a, &mult, c);
  return (c);
}
