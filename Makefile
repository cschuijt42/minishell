# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mde-cloe <mde-cloe@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/02/17 16:22:14 by mde-cloe      #+#    #+#                  #
#    Updated: 2023/02/17 16:22:14 by mde-cloe      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#General----------

NAME 			:= swaggyshell
CC				= gcc
COMPIL_FLAGS	?= #-Wall -Wextra -Werror
DEBUG_FLAGS		?= -g
LINKFLAGS 		?= -I include -I LIBFT/include

#sources and objects -------------

SOURCEFILES	:=	main.c \
				lexing.c \

OFILES	:=	$(SOURCEFILES:.c=.o)
SRC_DIR	:=	./sources/
OBJ_DIR	:=	./objects/
SOURCES	:=	$(addprefix $(SRC_DIR), $(SOURCEFILES))
OBJS	:=	$(addprefix $(OBJ_DIR), $(OFILES))

#-----------------targets---------------

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS) $(SRCS)
	@printf "$(C_GREEN)compiling! $(C_ORANGE)$@\n"
	@$(CC) $(OBJS) $(COMPIL_FLAGS) -o $@ $(LINKFLAGS) LIBFT/libft.a -g -lreadline
	@printf "\n **$(C_BOLD)$(C_CYAN)all done <3$(C_ORANGE)s**\n$(C_RESET)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(COMPIL_FLAGS) -o $@ $(LINKFLAGS) -c $< -g
	@printf "$(C_GREEN)Compiling $(C_CYAN)$(notdir $<) \n$(C_RESET)"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

clean:
	@$(RM) -rf $(OBJ_DIR)
	@printf "$(C_RED)Files cleaned\n$(C_RESET)"

fclean: clean
	@rm -f $(NAME)

re: fclean all

test: $(NAME)
	./swaggyshell

#colours---------------

C_RED		= \x1b[38;2;255;0;0m
C_LRED		= \x1b[38;2;255;128;128m
C_DRED		= \x1b[38;2;128;0;0m
C_LORANGE	= \x1b[38;2;255;192;128m
C_ORANGE	= \x1b[38;2;255;128;0m
C_DORANGE	= \x1b[38;2;128;64;0m
C_LYELLOW	= \x1b[38;2;255;255;128m
C_YELLOW	= \x1b[38;2;255;255;0m
C_DYELLOW	= \x1b[38;2;128;128;0m
C_LCHRT		= \x1b[38;2;192;255;128m
C_CHRT		= \x1b[38;2;128;255;0m
C_DCHRT		= \x1b[38;2;64;128;0m
C_LGREEN	= \x1b[38;2;128;255;128m
C_GREEN		= \x1b[38;2;0;255;0m
C_LCYAN		= \x1b[38;2;128;255;255m
C_CYAN		= \x1b[38;2;0;255;255m
C_DCYAN		= \x1b[38;2;0;128;128m
C_LAZURE	= \x1b[38;2;0;192;255m
C_AZURE		= \x1b[38;2;0;128;255m
C_DAZURE	= \x1b[38;2;0;64;128m
C_LBLUE		= \x1b[38;2;128;128;255m
C_BLUE		= \x1b[38;2;0;0;255m
C_DBLUE		= \x1b[38;2;0;0;128m
C_LVIOLET	= \x1b[38;2;192;0;255m
C_VIOLET	= \x1b[38;2;128;0;255m
C_DVIOLET	= \x1b[38;2;64;0;255m

C_RESET	= \x1b[0m
C_BOLD	= \x1b[1m