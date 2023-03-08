#General----------

NAME 			    := minishell
CC				    := gcc
COMPIL_FLAGS	?= #-Wall -Wextra -Werror
DEBUG_FLAGS		?= -g
LINKFLAGS 		?= -I include -I LIBFT/include

#sources and objects -------------

SOURCEFILES	:=	main.c \
								environment.c \
								lexing.c \
								lexing_utils.c \
								lexing_condensing.c \
								lexing_expanding.c \
								parsing.c \
								dir_builtins.c

OFILES	:=	$(SOURCEFILES:.c=.o)
SRC_DIR	:=	sources/
OBJ_DIR	:=	objects/
SOURCES	:=	$(addprefix $(SRC_DIR), $(SOURCEFILES))
OBJS	  :=	$(addprefix $(OBJ_DIR), $(OFILES))
LIBFT_A :=  ./LIBFT/libft.a

#-----------------targets---------------

all : $(NAME)

$(NAME) : $(LIBFT_A) $(OBJS)
	@printf "$(COMP_HEADER)$(C_LGREEN)$@$(COMP_AFTER)"
	@$(CC) $(OBJS) $(COMPIL_FLAGS) -o $@ $(LINKFLAGS) $(LIBFT_A) -g -lreadline
	@printf "$(COMP_DONE)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR)
	@printf "$(COMP_HEADER)$(notdir $<)$(COMP_AFTER)"
	@$(CC) $(COMPIL_FLAGS) -o $@ $(LINKFLAGS) -c $^ -g
	@printf "$(COMP_DONE)"

objects :
	@mkdir $(OBJ_DIR)

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)

$(LIBFT_A) :
	@printf "$(C_GREEN)Compiling $(C_CYAN)LIBFT \n$(C_RESET)"
	make -C LIBFT

clean:
	@$(RM) -rf $(OBJ_DIR)
	@printf "$(C_RED)Files cleaned\n$(C_RESET)"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.phony : clean fclean all re

# Fancy shmancy

COMP_HEADER = $(C_ORANGE)Compiling: $(C_CYAN)$(C_BOLD)
COMP_AFTER  = $(C_RESET)$(C_ORANGE)... $(C_RESET)
COMP_DONE   = $(C_GREEN)(Done!)$(C_RESET)\n

C_RED		  = \e[38;2;255;0;0m
C_LRED		= \e[38;2;255;128;128m
C_DRED		= \e[38;2;128;0;0m
C_LORANGE	= \e[38;2;255;192;128m
C_ORANGE	= \e[38;2;255;128;0m
C_DORANGE	= \e[38;2;128;64;0m
C_LYELLOW	= \e[38;2;255;255;128m
C_YELLOW	= \e[38;2;255;255;0m
C_DYELLOW	= \e[38;2;128;128;0m
C_LCHRT		= \e[38;2;192;255;128m
C_CHRT		= \e[38;2;128;255;0m
C_DCHRT		= \e[38;2;64;128;0m
C_LGREEN	= \e[38;2;128;255;128m
C_GREEN		= \e[38;2;0;255;0m
C_LCYAN		= \e[38;2;128;255;255m
C_CYAN		= \e[38;2;0;255;255m
C_DCYAN		= \e[38;2;0;128;128m
C_LAZURE	= \e[38;2;0;192;255m
C_AZURE		= \e[38;2;0;128;255m
C_DAZURE	= \e[38;2;0;64;128m
C_LBLUE		= \e[38;2;128;128;255m
C_BLUE		= \e[38;2;0;0;255m
C_DBLUE		= \e[38;2;0;0;128m
C_LVIOLET	= \e[38;2;192;0;255m
C_VIOLET	= \e[38;2;128;0;255m
C_DVIOLET	= \e[38;2;64;0;255m

C_RESET	  = \e[0m
C_BOLD	  = \e[1m
