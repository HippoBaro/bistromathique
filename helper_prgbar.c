/*
** helper_prgbar.c for Bistromathique in /home/barrau_h/Desktop/Bistromathique
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sat Nov 15 00:14:40 2014 Hippolyte Barraud
** Last update Sat Nov 15 03:03:55 2014 Hippolyte Barraud
*/

#include"include/bistromatique.h"

void print_progress(int step, int total, int *last_i, int new_i, int p)
{
  int pwidth;
  int width;
  int pos;
  int percent;
  int i;

  if (*last_i == new_i || p == 0)
    return;
  pwidth = 72;
  width = pwidth - strlen("calc : ");
  pos = (step * width) / total;
  percent = (step * 100) / total;
  printf("calc : [");
  i = 0;
  while (i < pos)
    {
      printf("%c", '=');
      i++;
    }
  printf("% *c", width - pos + 1, ']');
  printf(" %3d%%\r", percent);
  fflush(0);
}
