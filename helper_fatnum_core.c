/*
** helper_fatnum_core.c for Bistromatique in /home/barrau_h/Desktop/Bistromatique FINAL/Bistromatique
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sun Nov  9 04:39:50 2014 Hippolyte Barraud
** Last update Sat Nov 15 13:55:44 2014 Hippolyte Barraud
*/

#include"include/bistromatique.h"

/*
** Print a fatnum. If a custom operator set is given, uses it to display the
** correct minus character.
*/
void print_t_fatnum(t_fatnum *n, char *operators)
{
  register int i;

  if (n->signbit == MINUS)
    my_putchar(operators[3]);
  i = n->len;
  while (i >= 0)
    {
      my_putchar('0' + n->digits[i]);
      i--;
    }
  my_putchar('\n');
}

/*
** Initialize n and set it to zero. Whitout the reuse feature implemented,
** this function getted called thousands of times, that represented about
** 80 % of compute time for a 128Kb test file. Now, it only takes 22 % on
** the same file, speeding up the process as hell.
*/
inline void init_fatnum(register t_fatnum *n)
{
  register int i;
  register int to;

  to = MAXDIGITS;
  n->signbit = PLUS;
  if (n->init == 1)
    to = n->len + 1;
  i = 0;
  while (i < to)
      n->digits[i++] = '\0';
  n->len = 0;
  n->init = 1;
}

/*
** Initialize n and convert str to fatnum.
** Note that str can contain non-numerical characters. If so, the function
** stop and return what could be converted that far.
** Ex : "42*2" returns (fatnum)42.
** Also note that this function only create positive fatnum. This is because
** of postfix notation. If the number is negative, it'll be set by it's unary
** operator.
*/
inline t_fatnum *init_fatnum_with_val(char *str, t_fatnum *out, char *base)
{
  register int i;
  char *tempnum;

  i = 0;
  init_fatnum(out);
  out->signbit = PLUS;
  while (my_isdigit(str[i], base))
    i++;
  tempnum = my_strndup(str, i);
  if (strcmp(base, INTERN_BASE) == 0)
    out = str_to_fatnum(tempnum, out);
  else
    out = from_base_to_decimal(tempnum, base, out);
  free(tempnum);
  format_fatnum(out);
  return (out);
}
