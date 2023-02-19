OBJFILES := ft_atoi.o ft_isalnum.o ft_isalpha.o ft_isascii.o ft_isdigit.o \
					ft_isprint.o ft_strlen.o ft_substr.o ft_tolower.o ft_toupper.o \
					ft_itoa.o ft_strchr.o ft_strrchr.o ft_strdup.o ft_memset.o \
					ft_bzero.o ft_memchr.o ft_memcmp.o ft_memcpy.o ft_memmove.o \
					ft_calloc.o ft_strncmp.o ft_strlcat.o ft_strlcpy.o ft_strnstr.o \
					ft_split.o ft_strtrim.o ft_strmapi.o ft_striteri.o ft_putchar_fd.o \
					ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o ft_strjoin.o \
					ft_putnbr_base.o ft_lstadd_back.o ft_lstadd_front.o ft_lstclear.o \
					ft_lstdelone.o ft_lstiter.o ft_lstlast.o ft_lstmap.o ft_lstnew.o \
					ft_lstsize.o ft_putnbr_base.o ft_printf.o print_functions.o \
					get_next_line.o get_next_line_utils.o ft_strchrc.o exit_message.o \
					exit_perror.o free_array.o ft_exit.o ft_calloc_exit.o ft_abs.o
FLAGS = -Werror -Wall -Wextra
NAME = libft.a

$(NAME) : $(OBJFILES)
	ar rcs $(NAME) $(OBJFILES)

all : $(NAME)

re : fclean all

clean :
	rm -f $(OBJFILES)

fclean :
	rm -f $(NAME) $(OBJFILES)

%.o : %.c libft.h
	$(CC) -c $(FLAGS) -o $@ $<

.PHONY : clean fclean re
