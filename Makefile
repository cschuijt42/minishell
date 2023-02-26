#General----------

NAME 			    := minishell
CC				    := gcc
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
OBJS	  :=	$(addprefix $(OBJ_DIR), $(OFILES))
LIBFT_A :=  ./LIBFT/libft.a

#-----------------targets---------------

all: $(NAME)

$(NAME): $(OBJS) $(SRCS) $(LIBFT_A)
	@printf "$(C_GREEN)compiling! $(C_ORANGE)$@\n"
	@$(CC) $(OBJS) $(COMPIL_FLAGS) -o $@ $(LINKFLAGS) $(LIBFT_A) -g -lreadline
	@printf "\n **$(C_BOLD)$(C_CYAN)all done <3$(C_ORANGE)**\n$(C_RESET)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR)
	@printf "$(C_GREEN)Compiling $(C_CYAN)$(notdir $<) \n$(C_RESET)"
	@$(CC) $(COMPIL_FLAGS) -o $@ $(LINKFLAGS) -c $< -g

$(OBJ_DIR):
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

test: $(NAME)
	./swaggyshell

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
