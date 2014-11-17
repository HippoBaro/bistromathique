/*
** main.c for Bistromatique in /home/barrau_h/Desktop/Bistromatique FINAL/Bistromatique
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sun Nov  9 06:07:38 2014 Hippolyte Barraud
** Last update Sat Nov 15 14:01:26 2014 Hippolyte Barraud
*/

#include"include/bistromatique.h"

/*
** Helper function. Given by the suject.
*/
int my_atoi(char *c)
{
  int value = 0;
  int sign = 1;

  if (*c == '+' || *c == '-')
    {
      if (*c == '-')
	sign = -1;
      c++;
    }
  while (*c >= '0' && *c <= '9')
    {
      value *= 10;
      value += (int)(*c - '0');
      c++;
    }
  return (value * sign);
}

/*
** Helper function. Given by the suject.
*/
void check_base(char *b)
{
  if (my_strlen(b) < 2)
    print_fatal_error(1);
}

/*
** The get_expr given with the subject was real crap. Because the data received
** by this program can be arbitrary long, making a single call to read is
** stupid, for it relies on the hope that the data will be all there at once.
** Instead, we use a buffer to collect what we can until everything is there.
**
** SINCE THE COLLE OF 13/11/2014, this function have been corrected to avoid
** the SIGSEGV discovered back then. The changes are minors, but criticals.
*/
char *get_expr(unsigned int size)
{
  char *expr;
  char *buffer;
  int ret;
  unsigned long c;
  int buff_s;

  buff_s = 9990000;
  if (size < 9990000)
    buff_s = size;
  c = 0;
  ret = 0;
  if (size <= 1)
    print_fatal_error(2);
  buffer = malloc_or_die(sizeof(char) * buff_s + 1);
  expr = malloc_or_die(sizeof(char) * size + 1);
  expr[0] = 0;
  buffer[0] = 0;
  while (c < size)
    {
      ret = read(0, buffer, buff_s - 1);
      if (ret == -1)
	    print_fatal_error(4);
      else if (ret == 0)
      	break;
      buffer[ret] = 0;
      c = c + ret;
      my_strcat(expr, buffer);
    }
  expr[size] = 0;
  free(buffer);
  return (expr);
}

/*
** Helper function. Given by the suject.
*/
void check_ops(char *ops)
{
  if (my_strlen(ops) != 7)
    print_fatal_error(5);
}

/*
** Main function. Given by the subject.
** When you use this program to compute very large numbers, use the -p
** parramater to enable progress bar display.
** Ex : ./calc "01" "()+-x/%" 999999999 -p
*/
int main(int ac, char **av)
{
  unsigned int size;
  char *expr;
  int p;

  p = 0;
  if (ac != 4 && ac != 5)
    {
     my_putstr("Usage : ");
     my_putstr(av[0]);
     my_putstr(" base (\"0123456789\") ops (\"()+-*/%\") exp_len\n");
     exit(1);
   }
  else if (ac == 5 && strcmp(av[4], "-p") == 0)
    p = 1;
  check_base(av[1]);
  check_ops(av[2]);
  size = my_atoi(av[3]);
  expr = get_expr(size);
  eval_expr(av[1], av[2], expr, size, p);
  free(expr);
  exit(0);
}
