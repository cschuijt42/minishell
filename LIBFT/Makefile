# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mde-cloe <mde-cloe@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2021/12/13 18:00:17 by mde-cloe      #+#    #+#                  #
#    Updated: 2023/01/06 22:19:15 by mde-cloe      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#------General----------

NAME			:= libft.a
CC				?= gcc
WARN_FLAGS		?= -Wall -Wextra -Werror
INCLUDE_FLAGS 	?= -I include

#----cfiles-----

STRING :=	ft_split.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_strrcmp.c \
			ft_isalpha.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			str_reverse.c \

GNL	:= 		get_next_line.c \
			get_next_line_utils.c \
			get_next_line_bonus.c \
			get_next_line_utils_bonus.c

LIST :=		ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c

CONVERT	:=	ft_atoi.c \
			ft_itoa.c

MEM :=		ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_bzero.c \
			ft_calloc.c

PRINT :=	ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_print_map.c

PRINTF :=	ft_printf.c \
			char_printers.c \
			hex_printers.c \
			nbr_printers.c \

MISC :=		free_map.c

GNLPATH = $(addprefix gnl/, $(GNL))
PRINTFPATH = $(addprefix printf/, $(PRINTF))

MEMPATH := $(addprefix mem/, $(MEM))
MISCPATH := $(addprefix misc/, $(MISC))
PRINTPATH := $(addprefix printing/, $(PRINT) $(PRINTFPATH))
CONVERTPATH := $(addprefix convert/, $(CONVERT))
STRINGPATH := $(addprefix string/, $(STRING) $(GNLPATH))
LISTPATH := $(addprefix list/, $(LIST))

#----other variables----

SRC_DIR := ./sources/
OBJ_DIR := objects/

SRC :=	$(addprefix $(SRC_DIR), $(MISCPATH) $(PRINTPATH) $(CONVERTPATH) \
$(MEMPATH) $(LISTPATH) $(STRINGPATH))

OBJ :=	$(addprefix $(OBJ_DIR), $(notdir $(SRC:.c=.o)))


#-----------------targets---------------

all: $(NAME)

$(NAME): $(OBJ) | $(OBJ_DIR)
	@printf "$(C_LORANGE)\n BUILDING LIBRARY \n"
	@ar -rcs $@ $<
	@printf "$(YELLOW) $@ $(GREEN)(DONE) \n"

$(OBJ_DIR)%.o : $(SRC_DIR)*/%.c | $(OBJ_DIR)
	@$(CC) -c $<  -o $@ $(WARN_FLAGS) $(INCLUDE_FLAGS)
	@printf "$(BLUE) $(notdir $@) $(GREEN) (DONE) $(BLUE)$(C_RESET)\n"

$(OBJ_DIR)%.o : $(SRC_DIR)*/*/%.c | $(OBJ_DIR)
	@$(CC) -c $< -o $@ $(WARN_FLAGS) $(INCLUDE_FLAGS) && printf "$(BLUE) $(notdir $@) $(GREEN) (DONE) $(BLUE)$(C_RESET)\n"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

print:
	@printf "$(OBJ_DIR)"

#-----extra-----------

clean:
	@$(RM) -rf $(OBJ_DIR)
	@printf "$(C_RED)Files cleaned\n$(C_RESET)"

fclean: clean
	@rm -f $(NAME)


re: fclean all

.PHONY: all clean fclean re bonus

BLUE = \x1b[34;01m
GREEN = \x1b[32;01m
WHITE = \x1b[31;37m
YELLOW = \x1b[33;01m
RED = \x1b[31;01m
C_RESET	= \x1b[0m
C_LORANGE	= \x1b[38;2;255;192;128m
C_RED		= \x1b[38;2;255;0;0m