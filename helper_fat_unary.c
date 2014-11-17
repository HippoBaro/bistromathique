/*
** helper_fat_unary.c for Bistromatique in /home/barrau_h/Desktop/Bistromatique FINAL/Bistromatique
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sun Nov  9 04:38:00 2014 Hippolyte Barraud
** Last update Sun Nov  9 04:38:39 2014 Hippolyte Barraud
*/

#include"include/bistromatique.h"

/*
** Returns the opposite of a.
*/
t_fatnum *unary_minus(t_fatnum *a, t_fatnum *b, t_fatnum *c)
{
  c = fatnum_dup(a, c);
  if (c->signbit == MINUS)
    c->signbit = PLUS;
  else
    c->signbit = MINUS;
  return (c);
}

/*
** Returns the absolute value of a.
*/
t_fatnum *unary_abs(t_fatnum *a, t_fatnum *b, t_fatnum *c)
{
  c = fatnum_dup(a, c);
  c->signbit = PLUS;
  return (c);
}
