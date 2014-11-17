##
## Makefile for Bistromatique in /home/barrau_h/Desktop/Bistromatique FINAL/Bistromatique
## 
## Made by Hippolyte Barraud
## Login   <barrau_h@epitech.net>
## 
## Started on  Sun Nov  9 05:44:00 2014 Hippolyte Barraud
## Last update Sat Nov 15 00:18:37 2014 Hippolyte Barraud
##

CC =	gcc
RM =	rm -f
NAME =	calc
SRCS =	helper_fatnum_core.c \
	helper_fat_unary.c \
	helper_fat_pow.c \
	helper_fat_operator.c \
	helper_reuse.c \
	helper_error_handling.c \
	helper_fat_subtraction.c \
	helper_fatnum_utils.c \
	helper_fatnum_utils2.c \
	helper_pile.c \
	helper_base.c \
	helper_fat_add.c \
	helper_string.c \
	main.c \
	eval_expr.c \
	miscs.c \
	helper_prgbar.c

OBJS =	$(SRCS:.c=.o)

all:	$(NAME)

$(NAME):$(OBJS)
	$(CC) $(OBJS) -O3 -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
