/*
** helper_fatnum_utils2.c for Bistromatique in /home/barrau_h/Desktop/bistro
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sun Nov  9 23:15:51 2014 Hippolyte Barraud
** Last update Sat Nov 15 02:43:06 2014 Hippolyte Barraud
*/
#include"include/bistromatique.h"

/*
** Rarely, when the program needs to compare a fatnum to an int (like 1, for
** exemple), we need to create a fatnum instance based on that int.
** This function serves this purpose. It does NOT limit the program in any way.
*/
int fatnum_to_int(t_fatnum *num)
{
  int	out;
  register int	i;

  i = num->len;
  out = 0;
  while (i >= 0)
    {
      out *= 10;
      out += (int)(num->digits[i]);
      i--;
    }
  return (out);
}

/*
** Same as above, but the contary.
*/
t_fatnum *int_to_fatnum(register int s, t_fatnum *n)
{
  register int	t;

  if (s >= 0)
    n->signbit = PLUS;
  else
    n->signbit = MINUS;
  init_fatnum(n);
  n->len = -1;
  t = s;
  while (t > 0)
    {
      n->len++;
      n->digits[n->len] = (t % 10);
      t = t / 10;
    }
  if (s == 0)
    n->len = 0;
  return (n);
}

/*
** This function is only called if the user's base is the internal base
** (decimal) for faster conversion.
*/
t_fatnum *str_to_fatnum(char *str, t_fatnum *out)
{
  register int	i;
  register int	j;

  j = 0;
  i = my_strlen(str) - 1;
  out->len = i;
  out->signbit = PLUS;
  while (i >= 0)
    out->digits[j++] = str[i--] - '0';
  return (out);
}
