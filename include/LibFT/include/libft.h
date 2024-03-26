/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:20:15 by atresall          #+#    #+#             */
/*   Updated: 2024/02/13 14:55:46 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*----------Include----------*/
# include <inttypes.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

/*----------Struct-----------*/
/*
 * List for chain list
 */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/*--------Prototype----------*/

/*---Get---*/

/*
 * Get the number of digits in a long long integer
 * Parameters:
 *- num: The number for which to count digits
 */
int					ft_getdigits(long long num);

/*---Is---*/

/*
 * Check if a character is alphanumeric
 * Parameters:
 *- c: The character to check
 */
int					ft_isalnum(int c);

/*
 * Check if a character is alphabetic
 * Parameters:
 *- c: The character to check
 */
int					ft_isalpha(int c);

/*
 * Check if a character is ASCII
 * Parameters:
 *- c: The character to check
 */
int					ft_isascii(int c);

/*
 * Check if a character is a digit
 * Parameters:
 *- c: The character to check
 */
int					ft_isdigit(int c);

/*
 * Check if a character is printable
 * Parameters:
 *- c: The character to check
 */
int					ft_isprint(int c);

/*---Mem---*/

/*
 * Set a block of memory to zero
 * Parameters:
 *- s: Pointer to the memory block
 *- n: Number of bytes to set to zero
 */
void				ft_bzero(void *s, size_t n);

/*
 * Locate a character in a block of memory
 * Parameters:
 *- memoryBlock: Pointer to the memory block
 *- searchChar: Character to search for
 *- size: Number of bytes to search within
 */
void				*ft_memchr(const void *memoryBlock, int searchChar,
						size_t size);

/*
 * Compare two blocks of memory
 * Parameters:
 *- str1: Pointer to the first memory block
 *- str2: Pointer to the second memory block
 *- n: Number of bytes to compare
 */
int					ft_memcmp(const void *str1, const void *str2, size_t n);

/*
 * Copy a block of memory
 * Parameters:
 *- destination: Pointer to the destination memory block
 *- source: Pointer to the source memory block
 *- size: Number of bytes to copy
 */
void				*ft_memcpy(void *destination, const void *source,
						size_t size);

/*
 * Copy a block of memory, handling overlapping blocks
 * Parameters:
 *- destination: Pointer to the destination memory block
 *- source: Pointer to the source memory block
 *- n: Number of bytes to copy
 */
void				*ft_memmove(void *destination, const void *source,
						size_t n);

/*
 * Set a block of memory to a specified value
 * Parameters:
 *- pointer: Pointer to the memory block
 *- value: Value to set
 *- size: Number of bytes to set
 */
void				*ft_memset(void *pointer, int value, size_t size);

/*
 * Allocate memory for an array of elements
 * Parameters:
 *- elementCount: Number of elements to allocate memory for
 *- elementSize: Size of each element in bytes
 */
void				*ft_calloc(size_t elementCount, size_t elementSize);

/*
 * Reallocate memory for an existing pointer
 * Parameters:
 *- ptr: Pointer to the previously allocated memory
 *- newSize: New size in bytes
 */
void				*ft_realloc(void *ptr, size_t old_size, size_t new_size);

/*---Str---*/

/*
 * Locate the first occurrence of a character in a string
 * Parameters:
 *- str: The string to search in
 *- searchChar: The character to search for
 */
char				*ft_strchr(const char *str, int searchChar);

/*
 * Duplicate a string and malloc it
 * Parameters:
 *- str1: The string to duplicate
 */
char				*ft_strdup(const char *str1);

/*
 * Concatenate strings with size limitation
 * Parameters:
 *- destination: Pointer to the destination string
 *- source: Pointer to the source string
 *- size: Size of the destination buffer
 */
size_t				ft_strlcat(char *destination, const char *source,
						size_t size);

/*
 * Copy strings with size limitation
 * Parameters:
 *- dest: Pointer to the destination string
 *- src: Pointer to the source string
 *- size: Size of the destination buffer
 */
size_t				ft_strlcpy(char *dest, char *src, size_t size);

/*
 * Get the length of a string
 * Parameters:
 *- str: The string to calculate length for
 */
size_t				ft_strlen(const char *str);

/*
 * Get the length of a string up to a specified number of characters
 * Parameters:
 *- str: The string to calculate length for
 *- maxlen: Maximum number of characters to count
 */
size_t				ft_strnlen(const char *str, size_t maxlen);

/*
 * Compare two strings up to a specified number of characters
 * Parameters:
 *- s1: First string to compare
 *- s2: Second string to compare
 *- n: Number of characters to compare
 */
int					ft_strncmp(char *s1, char *s2, size_t n);

/*
 *Compare two string up
 *Parameters:
 *- s1: First string to compare
 *- s2: Second string to compare
 */
int					ft_strcmp(const char *s1, const char *s2);

/*
 * Locate a substring in a string
 * Parameters:
 *- source: The string to search in
 *- search: The substring to search for
 *- size: Maximum number of characters to search
 */
char				*ft_strnstr(const char *source, const char *search,
						size_t size);

/*
 * Locate the last occurrence of a character in a string
 * Parameters:
 *- str: The string to search in
 *- ch: The character to search for
 */
char				*ft_strrchr(const char *str, int ch);

/*
 * Extract a substring from a string
 * Parameters:
 *- s: The string to extract from
 *- start: The starting index of the substring
 *- len: The length of the substring
 */
char				*ft_substr(char const *s, unsigned int start, size_t len);

/*
 * Concatenate two strings
 * Parameters:
 *- s1: The first string
 *- s2: The second string
 */
char				*ft_strjoin(char const *s1, char const *s2);

/*
 * Trim characters specified in 'set' from the beginning and end of a string
 * Parameters:
 *- s1: The string to trim
 *- set: The set of characters to trim
 */
char				*ft_strtrim(char const *s1, char const *set);

/*
 * Split a string into an array of substrings based on a delimiter character
 * Parameters:
 *- s: The string to split
 *- c: The delimiter character
 */
char				**ft_split(char const *s, char c);

/*
 * Apply a function to each character of a string
 * Parameters:
 *- s: The string to iterate through
 *- f: The function to apply
 */
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/*
 * Iterate through a string and apply a function to each character
 * Parameters:
 *- s: The string to iterate through
 *- f: The function to apply
 */
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

/*
 * Reverse a string
 * Parameters:
 *- str: The string to reverse
 */
char				*ft_strrev(char *str);

/*---To---*/

/*
 * Convert a character to lowercase
 * Parameters:
 *- c: The character to convert
 */
int					ft_tolower(int c);

/*
 * Convert a character to uppercase
 * Parameters:
 *- c: The character to convert
 */
int					ft_toupper(int c);

/*
 * Convert a string to an integer
 * Parameters:
 *- str: The string to convert
 */
int					ft_atoi(const char *str);

/*
 * Convert an integer to a string
 * Parameters:
 *- n: The integer to convert
 */
char				*ft_itoa(int n);

/*
 * Convert a size_t number to a hexadecimal string
 * Parameters:
 *- num: The size_t number to convert
 */
char				*ft_ltoh(size_t num);

/*---Put---*/

/*
 * Print a character to a file descriptor
 * Parameters:
 *- c: The character to print
 *- fd: File descriptor
 */
int					ft_putchar_fd(char c, int fd);

/*
 * Print a string to a file descriptor
 * Parameters:
 *- s: The string to print
 *- fd: File descriptor
 */
int					ft_putstr_fd(char *s, int fd);

/*
 * Print a string followed by a newline to a file descriptor
 * Parameters:
 *- s: The string to print
 *- fd: File descriptor
 */
int					ft_putendl_fd(char *s, int fd);

/*
 * Print an integer to a file descriptor
 * Parameters:
 *- n: The integer to print
 *- fd: File descriptor
 */
int					ft_putnbr_fd(ssize_t n, int fd);

/*
 * Print a pointer address to a file descriptor in hexadecimal format
 * Parameters:
 *- num: The pointer address
 *- base: The base of the output (e.g., "0123456789abcdef")
 *- fd: File descriptor
 */
int					ft_putptr_fd(uintptr_t num, const char *base, int fd);

/*
 * Print an unsigned integer to a file descriptor in hexadecimal format
 * Parameters:
 *- num: The unsigned integer
 *- base: The base of the output (e.g., "0123456789abcdef")
 *- fd: File descriptor
 */
int					ft_puthex_fd(unsigned int num, const char *base, int fd);

/*---List---*/

/*
 * Create a new linked list element
 * Parameters:
 *- content: The content to be added to the list node
 */
t_list				*ft_lstnew(void *content);

/*
 * Add a new element at the beginning of a linked list
 * Parameters:
 *- lst: The address of a pointer to the first link of a list
 *- new: The element to add at the beginning of the list
 */
void				ft_lstadd_front(t_list **lst, t_list *new);

/*
 * Count the number of elements in a linked list
 * Parameters:
 *- lst: The beginning of the linked list
 */
int					ft_lstsize(t_list *lst);

/*
 * Get the last element of a linked list
 * Parameters:
 *- lst: The beginning of the linked list
 */
t_list				*ft_lstlast(t_list *lst);

/*
 * Add a new element at the end of a linked list
 * Parameters:
 *- lst: The address of a pointer to the first link of a list
 *- new: The element to add at the end of the list
 */
void				ft_lstadd_back(t_list **lst, t_list *new);

/*
 * Delete an element from a linked list
 * Parameters:
 *- lst: The element to delete
 *- del: The function used to delete the content of the element
 */
void				ft_lstdelone(t_list *lst, void (*del)(void *));

/*
 * Delete an entire linked list
 * Parameters:
 *- lst: The address of a pointer to the first link of a list
 *- del: The function used to delete the content of each element
 */
void				ft_lstclear(t_list **lst, void (*del)(void *));

/*
 * Iterate through a linked list and apply a function to each element
 * Parameters:
 *- lst: The beginning of the linked list
 *- f: The function to apply to each element
 */
void				ft_lstiter(t_list *lst, void (*f)(void *));

/*
 * Create a new linked list by applying a function to each element of a list
 * Parameters:
 *- lst: The beginning of the linked list
 *- f: The function to apply to each element
 *- del: The function used to delete the content of each element if needed
 */
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

#endif
