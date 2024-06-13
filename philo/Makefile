# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpietrza <mpietrza@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/18 14:21:04 by mpietrza          #+#    #+#              #
#    Updated: 2024/06/13 14:54:36 by mpietrza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
DIR_OBJS	= ./objs/
INCLUDE		= philo.h
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -fsanitize=address# -g
RM			= rm -f

#COLORS
DEF_COLOR = "\033[39m"
GRAY = "\033[30m"
R = "\033[31m"
G = "\033[32m"
Y = "\033[33m"
B = "\033[34m"
M = "\033[35m"
C = "\033[36m"
W = "\033[37m"

#SOURCES

SRCS			= actions.c \
			  atoi_secured.c \
			  arg_check.c \
			  free_exit.c \
			  init_parse.c \
			  monitoring.c \
			  philo.c \
			  threads.c\
			  utils_time.c \
			 
OBJS		= $(addprefix $(DIR_OBJS), $(SRCS:.c=.o))

DEPS		= $(OBJS:.o=.d)

all:	$(DIR_OBJS) $(NAME)

-include $(DEPS)

$(DIR_OBJS)%.o : %.c
	@echo $(B)Compiling [$<]... $(DEF_COLOR)
	@printf $(Y) 
	$(CC) $(CFLAGS) -MMD -MP -c -o $@ $< 
	@echo $(DEF_COLOR)

$(DIR_OBJS):
	@echo $(B)Creating directory: $(DIR_OBJS)
	@printf $(Y)
	mkdir -p $(DIR_OBJS)
	@echo Directory 'objs' generated succesfully! $(DEF_COLOR)

$(NAME): $(OBJS) Makefile
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo $(G)Compiled successfully! $(DEF_COLOR)

clean:
	@echo $(GRAY)
	$(RM) -rf $(OBJS) $(DEPS) $(DIR_OBJS)
	@echo $(G)Object files erased successfully! $(DEF_COLOR)

fclean: clean
	@echo $(GRAY)
	$(RM) $(NAME)
	@echo $(G)Executable files erased succesfully! $(DEF_COLOR)
	
re:		fclean all
	@echo $(G)Erased and recompiled every file successfully! $(DEF_COLOR)

debug:
	@echo "Object files: $(OBJS)"
	@echo "Dependency files: $(DEPS)"

.PHONY: all clean fclean re debug
