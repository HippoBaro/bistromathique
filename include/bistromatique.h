/*
** bistromatique.h for Bistromatique in /home/barrau_h/Desktop/Bistromatique FINAL/Bistromatique
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sun Nov  9 04:27:14 2014 Hippolyte Barraud
** Last update Sat Nov 15 03:03:10 2014 Hippolyte Barraud
*/

#ifndef BISTROMATIQUE_H_
# define BISTROMATIQUE_H_

#include <stdlib.h>

#define MAXOP 9999
#define MAXFATNUM 9999
#define	MAXDIGITS 1200000
#define MAXREUSE 10000
#define INTERN_BASE "0123456789"
#define PLUS 1
#define MINUS -1
#define SYNTAXE_ERROR_MSG "syntax error\n"

enum { BINDTYPE_NONE = 0, BINDTYPE_LEFT = 1, BINDTYPE_RIGHT = 2 };
typedef struct s_fatnum {
  char	digits[MAXDIGITS];
  int	signbit;
  int	len;
  int   init;
} t_fatnum;

typedef struct s_op {
  char	op;
  int	prec;
  int	assoc;
  int	unary;
  t_fatnum *(*eval)(t_fatnum *a, t_fatnum *b, t_fatnum *c);
} t_op;

typedef struct s_root {
  t_op		*operator_stack[MAXOP];
  t_fatnum	*fatnum_stack[MAXFATNUM];
  t_fatnum  *reuse_stack[MAXREUSE];
  int		index_operator_stack;
  int		index_fatnum_stack;
  int		index_reuse;
  char		*check_start;
  t_op		start_operator;
  t_op		*op;
  t_op		*last_operator;
  char		*operator_list;
  char      *base;
} t_root;

int convert_to_inner_op(char *expr, char *cus_op);
t_fatnum *from_decimal_to_base(t_fatnum *n, char *base, t_fatnum *m);
t_fatnum *from_base_to_decimal(char *num, char *base, t_fatnum *s);
t_fatnum *int_to_fatnum(int s, t_fatnum *n);
void	format_fatnum_cus_zero(t_fatnum *n, char zero);
char *my_strcat(char *dest, char *src);
void	push_operator(t_op *op, t_root *stacks);
t_op	*pop_operator(t_root *stacks);
void	push_fatnum(t_fatnum *num, t_root *stacks);
t_fatnum *pop_fatnum(t_root *stacks);
void	process_postscript(t_fatnum *n1, t_fatnum *n2, t_op *pop,
			   t_root *stacks);
void	init(t_root*, char*);
void	my_putchar(char c);
void	my_putstr(char *str);
int	my_strlen(char *str);
char *my_strndup(char *src, int lim);
int	my_isdigit(char c, char *base);
int	my_isspace(char c, char *base);
int fatnum_to_int(t_fatnum *num);
void	print_fatal_error(int err);
void	*malloc_or_die(int n);
t_op	*getop(char ch);

t_fatnum *add(t_fatnum *a, t_fatnum *b, t_fatnum *c);
t_fatnum *subtract(t_fatnum *a, t_fatnum *b, t_fatnum *c);
t_fatnum *multiply(t_fatnum *a, t_fatnum *b, t_fatnum *c);
t_fatnum *divide(t_fatnum *a, t_fatnum *b, t_fatnum *c);
t_fatnum *mod(t_fatnum *a, t_fatnum *b, t_fatnum *c);
t_fatnum *unary_minus(t_fatnum *a, t_fatnum *b, t_fatnum *c);
t_fatnum *unary_abs(t_fatnum *a, t_fatnum *b, t_fatnum *c);
t_fatnum *fatpow(t_fatnum *a, int b, t_fatnum *c);
int	eval_expr(char *base, char *operators, char *expr, int size, int p);
int	is_fatnum_zero(t_fatnum *num);
void	format_fatnum(t_fatnum *n);
void	digit_shift(t_fatnum *n, int d);
void	print_t_fatnum(t_fatnum *n, char *operators);
void	init_fatnum(t_fatnum *n);
t_fatnum *init_fatnum_with_val(char *str, t_fatnum *out, char *base);
int	my_max(int a, int b);
int	fatnum_cmp(t_fatnum *a, t_fatnum *b);
t_fatnum *fatnum_dup(t_fatnum *src, t_fatnum *dest);
void register_for_reuse(t_root *stacks, t_fatnum *num);
t_fatnum *get_fatnum(t_root *stacks);
void clear_stacks(t_root *stacks);
t_fatnum *str_to_fatnum(char *str, t_fatnum *out);
void print_progress(int step, int total, int *last_i, int new_i, int p);

#endif
