/*
** helper_error_handling.c for Bistromatique in /home/barrau_h/Desktop/Bistromatique FINAL/Bistromatique
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sun Nov  9 04:11:45 2014 Hippolyte Barraud
** Last update Sat Nov 15 03:14:57 2014 Hippolyte Barraud
*/

#include"include/bistromatique.h"

/*
** Helper function. Ends the program with the according error message and exit
** code.
** The use of fflush is because of the progress bar. It can be safely delete.
*/
void print_fatal_error(int err)
{
  fflush(0);
  printf("\33[2K\r");
  fflush(0);
  if (err == 1)
    my_putstr("Bad base\n");
  else if (err == 2)
    my_putstr("Bad expr len\n");
  else if (err == 3)
    my_putstr("could not alloc\n");
  else if (err == 4)
    my_putstr("could not read\n");
  else if (err == 5)
    my_putstr("Bad ops\n");
  else if (err == 6)
    my_putstr(SYNTAXE_ERROR_MSG);
  else if (err == 7)
    my_putstr("division by zero\n");
  else if (err == 8)
    my_putstr("mod by zero\n");
  exit(err);
}

/*
** Helper function. The same as xmalloc.
*/
void	*malloc_or_die(int n)
{
  void	*p;

  p = (void*)malloc(n);
  if (p == NULL)
    print_fatal_error(3);
  return p;
}
