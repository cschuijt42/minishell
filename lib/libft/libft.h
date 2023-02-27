/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 16:44:15 by cschuijt      #+#    #+#                 */
/*   Updated: 2022/10/24 17:01:38 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// -- DEFAULT FUNCTIONS --

// Returns the length of the given string. No NULL protection.
size_t	ft_strlen(const char *s);
// Strips whitespace and up to one +/- from a string and returns the first
// integer value if it can find one.
int		ft_atoi(const char *s);
// Returns 1 if c is an upper or lowercase letter.
int		ft_isalpha(int c);
// Returns 1 if c is a letter or a digit.
int		ft_isalnum(int c);
// Returns 1 if c is in the ascii table.
int		ft_isascii(int c);
// Returns 1 if c is a digit.
int		ft_isdigit(int c);
// Returns 1 if c is printable.
int		ft_isprint(int c);
// Turns uppercase letters into lowercase, returns c in all other cases.
int		ft_tolower(int c);
// Turns lowercase letters into uppercase, returns c in all other cases.
int		ft_toupper(int c);
// Returns a pointer to the first instance of c in s, or NULL if none found.
char	*ft_strchr(const char *s, int c);
// Returns a pointer to the last instance of c in s, or NULL if none found.
char	*ft_strrchr(const char *s, int c);
// Allocates and returns a string that is an exact copy of s.
char	*ft_strdup(const char *s);
// Sets n bytes of memory to c from pointer s.
void	*ft_memset(void *s, int c, size_t n);
// Sets n bytes of memory from pointer s to null bytes.
void	ft_bzero(void *s, size_t n);
// Returns a pointer to the first instance of c in n bytes of memory from s.
// No null byte limit.
void	*ft_memchr(const void *s, int c, size_t n);
// Compares two blocks of memory and returns s1 - s2 when they do not match.
int		ft_memcmp(const void *s1, const void *s2, size_t n);
// Copies n bytes of memory from src to dest. This one is overlap-safe.
void	*ft_memcpy(void *dest, const void *src, size_t n);
// Copies n bytes of memory from src to dest. This one is also overlap-safe.
void	*ft_memmove(void *dest, const void *src, size_t n);
// Allocates nmemb * size bytes of memory, and sets all those bytes to null.
void	*ft_calloc(size_t nmemb, size_t size);
// Compares two strings, returning s1 - s2 when they do not match.
int		ft_strncmp(const char *s1, const char *s2, size_t n);
// Copies string src to dest, not writing more than dstsize bytes, null
// inclusive. Return value is length of string it tried to write.
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
// Appends string src to dest, not checking or writing more than dstsize bytes.
// Safe to use on dst strings without a null terminator. Return value is
// length of string it tried to create.
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
// Finds the first occurrence of needle in haystack, not searching further than
// len bytes. If needle is empty, returns the entire haystack. If needle cannot
// be found, returns NULL.
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

// -- CUSTOM FUNCTIONS --

// Allocates and returns a string representation of integer n
char	*ft_itoa(int n);
// Splits string s by delimiter character c, returning a NULL-terminated
// array of strings with each substring found.
char	**ft_split(char const *s, char c);
// Allocates a trimmed version of s1, removing characters from the front
// and back that also occur in set.
char	*ft_strtrim(char const *s1, char const *set);
// Allocates and returns a string from string s which starts at index start and
// is at most len bytes long.
char	*ft_substr(char const *s, unsigned int start, size_t len);
// Allocates and returns a string, the contents of which are equal to each
// character in string s after being run through function f. Unsigned int in
// function prototype is the string index.
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
// Edits string s, overriding each character using function f. Unsigned int in
// function prototype is the string index.
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
// Allocates and returns a string, the contents of which is s1 and s2 combined.
char	*ft_strjoin(char const *s1, char const *s2);
// Writes a single character to the given file descriptor.
void	ft_putchar_fd(char c, int fd);
// Writes a string to the given file descriptor.
void	ft_putstr_fd(char *s, int fd);
// Writes a string to the given file descriptor, adding a newline at the end.
void	ft_putendl_fd(char *s, int fd);
// Writes an integer to the given file descriptor.
void	ft_putnbr_fd(int n, int fd);

// -- LINKED LIST FUNCTIONS -- 

// Adds list item new to the back of list lst. If lst is NULL, new becomes the
// first element in the list.
void	ft_lstadd_back(t_list **lst, t_list *new);
// Adds list item new to the front of list lst.
void	ft_lstadd_front(t_list **lst, t_list *new);
// Calls function del on the content of each element in list lst, then frees
// each element in the list.
void	ft_lstclear(t_list **lst, void (*del)(void*));
// Calls function del on the content of list element lst, then frees it.
void	ft_lstdelone(t_list *lst, void (*del)(void*));
// Calls function f on the content of each list element in lst, updating it
// as needed.
void	ft_lstiter(t_list *lst, void (*f)(void *));
// Returns a pointer to the last element of list lst.
t_list	*ft_lstlast(t_list *lst);
// Calls function f on the content of each list element in lst, creating a new
// list with its results. Function del is required to clean up in case of
// malloc failure.
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
// Creates a new list node with content pointer and next pointer NULL.
t_list	*ft_lstnew(void *content);
// Returns the amount of items in list lst.
int		ft_lstsize(t_list *lst);

// -- FT_PRINTF --

// Simple printf implementation that can handle the following flags:
// %c, %s, %p, %x, %X, %d, %i, %u, %%
int		ft_printf(const char *str, ...);

int		printf_nbr_b(int n, char *base);
int		printf_nbr_ub(unsigned int n, char *base);
int		printf_string(char *str);
int		printf_char(int c);
int		printf_pointer(unsigned long n);

// -- GET_NEXT_LINE --

// Returns an allocated string containing the next line from the given file
// descriptor, or NULL if there was an error/end of file was reached. Cleanup
// only happens at EOF/error. Define BUFFER_SIZE to determine how much of
// the file is read at once.
char	*get_next_line(int fd);

// -- OTHERS --

int		ft_put_nbr_base(size_t nbr, char *base);
// Returns the amount of occurrences of character c in string str.
size_t	ft_strchrc(char *str, char c);

// @brief Frees each element in a NULL-terminated array of pointers, then
// frees the array itself. Does not set array pointer to NULL.
void	free_array(void **array);

// @brief Prints "Error\n" on stderr, followed by a message, then exits the
// program with code 1.
void	exit_message(char *msg);

// @brief Calls perror with msg, then exits the program with code 1.
void	exit_perror(char *msg);

// @brief Prints "Error\n" on the standard error, then exits the program
// with code 1.
void	ft_exit(void);

void	*ft_calloc_exit(size_t nmemb, size_t size);

int		ft_abs(int i);

#endif
