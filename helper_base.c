/*
** helper_base.c for Bistromatique in /home/barrau_h/Desktop/Bistromathique
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sun Nov  9 23:26:23 2014 Hippolyte Barraud
** Last update Sat Nov 15 02:55:21 2014 Hippolyte Barraud
*/

#include"include/bistromatique.h"

/*
** Returns 1 if c is part of the input base. Same as isdigit dor decimal base.
*/
int	my_isdigit(char c, register char *base)
{
  register int i;

  i = 0;
  while (base[i] != '\0')
    {
      if (c == base[i])
	return (1);
      i++;
    }
  return (0);
}

/*
** Convert the internal fatum representation into a custom base special fatnum
** to display to the user. All interbal calculations are done into decimal
** base (wich is, when thinking about it, stupid ; but it's too late).
*/
t_fatnum *from_decimal_to_base(t_fatnum *n, char *base, t_fatnum *m)
{
  static t_fatnum b;
  register int i;
  static t_fatnum d;
  static t_fatnum zero;
  static t_fatnum n2;

  if (strcmp(base, INTERN_BASE) == 0)
    {
      free (m);
      return (n);
    }
  init_fatnum(m);
  init_fatnum(&zero);
  i = 0;
  int_to_fatnum(my_strlen(base), &b);
  fatnum_dup(n, &n2);
  n2.signbit = PLUS;
  m->signbit = n->signbit;
  while (fatnum_cmp(&n2, &zero) != 0)
    {
      divide(&n2, &b, &d);
      n2 = d;
      mod(&n2, &b, &d);
      m->digits[i++] = base[fatnum_to_int(&d)] - '0';
    }
  m->len = i;
  format_fatnum(m);
  return (m);
}

/*
** Returns the value of a chars depending on it's position into the base.
*/
int find_char_val(char c, char *base)
{
  register int i;

  i = 0;
  while (base[i] != '\0')
    {
      if (base[i] == c)
	return (i);
      i++;
    }
  print_fatal_error(6);
  return (1);
}

/*
** Convert the string representation of a fatnum into a decimal fatnum
** instance. While static variables are generally to avoid, they result in a
** great performance boost here. If they weren't, they would be fully
** initialized them at each call. Instead, we now only reinitialize what have
** been peviously used.
*/
t_fatnum *from_base_to_decimal(register char *num, char *base, t_fatnum *s)
{
  static t_fatnum n;
  static t_fatnum b;
  static t_fatnum one;
  static t_fatnum sub;
  static t_fatnum mult;
  static t_fatnum tmp;
  static t_fatnum sl;
  register int i;

  i = -1;
  init_fatnum(s);
  int_to_fatnum(1, &one);
  int_to_fatnum(my_strlen(num), &n);
  int_to_fatnum(my_strlen(base), &b);
  while (num[++i] != '\0')
    {
      subtract(&n, &one, &sub);
      fatnum_dup(&sub, &n);
      fatpow(&b, fatnum_to_int(&n), &sub);
      int_to_fatnum(find_char_val(num[i], base), &tmp);
      multiply(&tmp, &sub, &mult);
      add(s, &mult, &sl);
      fatnum_dup(&sl, s);
    }
  return (s);
}
