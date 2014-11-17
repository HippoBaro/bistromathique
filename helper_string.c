/*
** helper_string.c for Bistromatique in /home/barrau_h/Desktop/Bistromatique FINAL/Bistromatique
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sun Nov  9 05:41:55 2014 Hippolyte Barraud
** Last update Sat Nov 15 02:20:49 2014 Hippolyte Barraud
*/

#include"include/bistromatique.h"

int	my_strlen(char *str)
{
  register unsigned int	i;

  i = 0;
  while (str[i] != '\0')
    i++;
  return (i);
}

void	my_putchar(char c)
{
  write(1, &c, 1);
}

void	my_putstr(char *str)
{
  register unsigned int	i;

  i = 0;
  while (str[i] != '\0')
    my_putchar(str[i++]);
}

/*
** Note that the function check the passed char for presence in the base, if
** so, the function shall consider it as a number and won't ignore it.
*/
int	my_isspace(char c, char *base)
{
  if (my_isdigit(c, base))
    return (0);
  if (c == ' ')
    return (1);
  return (0);
}

char *my_strndup(char *src, int lim)
{
  char *result;
  register unsigned int	i;
  register unsigned int len;

  len = my_strlen(src);
  if (lim < len)
    len = lim;
  i = 0;
  result = (char *)malloc_or_die(len + 1);
  while (i < len)
    {
      result[i] = src[i];
      i++;
    }
  result[len] = '\0';
  return (result);
}
