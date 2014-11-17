/*
** helper_fat_pow.c for Bistromatique in /home/barrau_h/Desktop/bistro
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sun Nov  9 23:17:16 2014 Hippolyte Barraud
** Last update Sat Nov 15 02:35:00 2014 Hippolyte Barraud
*/
#include"include/bistromatique.h"

/*
** While power operation wasn't requested by the subject, this internal-only
** ("2^2" is not supported) is mendatory for base conversion on fatnum.
** It is only used in this purpose.
*/
t_fatnum	*fatpow(t_fatnum *a, register int b, t_fatnum *c)
{
  static t_fatnum tmp;

  if (b == 0)
    {
      int_to_fatnum(1, c);
      return (c);
    }
  c = fatnum_dup(a, c);
  b--;
  while (b > 0)
    {
      tmp = *fatnum_dup(c, &tmp);
      c = multiply(&tmp, a, c);
      b--;
    }
  return (c);
}
