# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/17 11:23:06 by kgrosjea     #+#   ##    ##    #+#        #
#    Updated: 2019/02/16 18:19:24 by kgrosjea    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

#__________CONFIG__________#

NAME		=	lem-in

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

LIB_FLAGS	=	-L$(LIB_PATH) $(LIB_FLAG)
INC_PREF	=	-I

SRC_PATH	=	./srcs/
BIN_PATH	=	./bins/
LIB_PATH	=	./libft/

INC			=	./includes/			\
				./libft/			\

SRC			=	main.c				\
				init_structs.c		\
				set_structs.c		\
				parsing.c			\
				check_format.c		\
				get_data.c			\
				fill_data.c			\
				check_data.c		\
				list_paths.c		\
				free_structs.c		\
				utils.c				\
				put_to_lib.c		\
				clean_data.c		\
				optimize_data.c		\
				update_data.c		\

BIN			=	$(SRC:.c=.o)

LIB_FLAG			=	-lft
LIB					=	libft.a		\

SRCS		=	$(addprefix $(SRC_PATH), $(SRC))
BINS		=	$(addprefix $(BIN_PATH), $(BIN))
LIBS		=	$(addprefix $(LIB_PATH), $(LIB))
INCS		=	$(addprefix $(INC_PREF), $(INC))

.PHONY: all clean fclean re norm debug noflag list

#__________COLORS__________#

R			=	\033[0;31m
G			=	\033[32;7m
B			=	\033[0;34m
N			=	\33[0;0m

#__________RULES__________#

all: $(NAME)

$(NAME): $(LIBS) $(BINS)

	@$(CC) $(CFLAGS) $(INCS) $(LIB_FLAGS) -o $@ $^ && echo "\n\n${B}[EXECUTABLE \"$(NAME) COMPILED\"]\n"

$(LIBS):

	@make -C $(LIB_PATH)

$(BIN_PATH)%.o: $(SRC_PATH)%.c

	@mkdir -p $(BIN_PATH) && 2> /dev/null
	@$(CC) $(INCS) $(CFLAGS) -o $@ -c $< && echo "${G} \c"

clean:

	@make clean -C $(LIB_PATH)
	@echo "${R}[CLEANING $(NAME) BINARIES]\n"
	@rm -f $(BINS)

fclean: clean

	@rm -rf $(LIB_PATH)$(LIB) && echo "${R}[REMOVING \"$(LIB)\"]\n"
	@echo "${R}[REMOVING \"$(NAME)\"]\n"
	@rm -f $(NAME)
	@mkdir -p $(BIN_PATH) && 2> /dev/null
	@rmdir $(BIN_PATH) && 2> /dev/null

re: fclean all

norm:

	@norminette -R CheckForbiddenSourceHeader ./srcs/ ./includes/

debug:

	@echo "\n${B}[COMPILING WITH DEBUG FLAGS]" && make debug -C $(LIB_PATH) && make CFLAGS=' -Wall -Wextra -Werror -g'

noflag:

	@echo "\n${B}[COMPILING WITH NO FLAGS]" && make re CFLAGS=''

list:

	@ar -t libftprintf.a
