#General----------
#O3
NAME 			    := minishell
CC				    := cc
COMPIL_FLAGS		?= -Wall -Wextra -Werror
UNAME_S       := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	READLINEFLAGS := -lreadline -L $(shell brew --prefix readline)/lib
else
	READLINEFLAGS := -lreadline
endif
ifeq ($(UNAME_S), Darwin)
	LINKFLAGS 		?= -I include -I LIBFT/include -I $(shell brew --prefix readline)/include
else
	LINKFLAGS 		?= -I include -I LIBFT/include
endif

#sources and objects -------------

SOURCEFILES	:=	builtin_execution.c \
				builtin_redirects.c \
				builtins_dir.c \
				builtins_env.c \
				builtins_misc.c \
				cleanup.c \
				environment.c \
				env_printing.c \
				env_recreation.c \
				env_utils.c \
				error_handling.c \
				execution_helpers.c \
				executor_child.c \
				executor.c \
				heredoc_expansion.c \
				heredoc.c \
				lexing.c \
				lexing_condensing.c \
				lexing_expanding.c \
				lexing_utils.c \
				main.c \
				parsing.c \
				path.c \
				redirects.c \
				shell_struct.c \
				signals.c

OFILES	:=	$(SOURCEFILES:.c=.o)
SRC_DIR	:=	sources/
OBJ_DIR	:=	objects/
SOURCES	:=	$(addprefix $(SRC_DIR), $(SOURCEFILES))
OBJS	  :=	$(addprefix $(OBJ_DIR), $(OFILES))
LIBFT_A :=  ./LIBFT/libft.a
LIBFT_H :=  ./LIBFT/include/libft.h

#-----------------debug---------------
ifdef DEBUG
COMPIL_FLAGS += -g
#-fsanitize=address -fno-omit-frame-pointer
endif

#-----------------targets---------------

all : $(NAME)

$(NAME) : $(LIBFT_A) $(OBJS)
	@printf "$(COMP_HEADER)$(C_LGREEN)$@$(COMP_AFTER)"
	@$(CC) $(OBJS) $(COMPIL_FLAGS) -o $@ $(LINKFLAGS) $(READLINEFLAGS) $(LIBFT_A)
	@printf "$(COMP_DONE)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR)
	@printf "$(COMP_HEADER)$(notdir $<)$(COMP_AFTER)"
	@$(CC) $(COMPIL_FLAGS) -o $@ $(LINKFLAGS) -c $^
	@printf "$(COMP_DONE)"

objects :
	@mkdir $(OBJ_DIR)

$(LIBFT_A) : $(LIBFT_H)
	@printf "$(C_GREEN)Compiling $(C_CYAN)LIBFT \n$(C_RESET)"
	make -C LIBFT

clean :
	@$(RM) -rf $(OBJ_DIR)
	@printf "$(C_RED)Files cleaned\n$(C_RESET)"

fclean : clean
	@rm -f $(NAME)

re:: fclean all

run : $(NAME)
	./minishell

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
