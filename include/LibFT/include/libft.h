/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:20:15 by atresall          #+#    #+#             */
/*   Updated: 2024/05/13 15:31:50 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <inttypes.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

/**
 * @struct s_list
 * @brief Une structure pour représenter une liste chaînée.
 *
 * @var s_list::content
 * Le membre 'content' contient les données du nœud de la liste.
 *
 * @var s_list::next
 * Le membre 'next' pointe vers le prochain nœud de la liste.
 */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/*
 *
 *     $$$$$$\  $$$$$$$\  $$$$$$$\   $$$$$$\ $$\     $$\  $$$$$$\
 *    $$  __$$\ $$  __$$\ $$  __$$\ $$  __$$\\$$\   $$  |$$  __$$\
 *    $$ /  $$ |$$ |  $$ |$$ |  $$ |$$ /  $$ |\$$\ $$  / $$ /  \__|
 *    $$$$$$$$ |$$$$$$$  |$$$$$$$  |$$$$$$$$ | \$$$$  /  \$$$$$$\
 *    $$  __$$ |$$  __$$< $$  __$$< $$  __$$ |  \$$  /    \____$$\
 *    $$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |   $$ |    $$\   $$ |
 *    $$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |   $$ |    \$$$$$$  |
 *    \__|  \__|\__|  \__|\__|  \__|\__|  \__|   \__|     \______/
 *
 */

/**
 * @brief Calcule la longueur d'un tableau.
 *
 * @param ARRAY: Le tableau dont on veut connaître la longueur.
 * @return La longueur du tableau.
 */
size_t				ft_arrlen(char **array);

/**
 * @brief Ajoute un element a une liste
 *
 * @param ARRAY: Le tableau au quel on ajoute une ligne
 * @param LINE: La ligne a ajouter
 * @return Retourne un pointeur vers le nouveau tableau
 */
char				**ft_arradd(char **array, char *line);

/**
 * @brief Duplique le tableau
 *
 * @param array
 * @return Retourne le pointeur vers le tableau dupliquer
 */
char				**ft_arrdup(char **array);

/**
 * @brief Supprime un element a la position voulu dans un tableau
 *
 * @param ARRAY: Tableau a modifier
 * @param POSITION: Position de la ligne a supprimer
 * @return Retourne le pointeur vers le tableau modifier
 */
char				**ft_arrdel(char **array, int position);

/*
 *     $$$$$$\  $$$$$$$$\ $$$$$$$$\ $$$$$$$$\ $$$$$$$$\ $$$$$$$\
 *    $$  __$$\ $$  _____|\__$$  __|\__$$  __|$$  _____|$$  __$$\
 *    $$ /  \__|$$ |         $$ |      $$ |   $$ |      $$ |  $$ |
 *    $$ |$$$$\ $$$$$\       $$ |      $$ |   $$$$$\    $$$$$$$  |
 *    $$ |\_$$ |$$  __|      $$ |      $$ |   $$  __|   $$  __$$<
 *    $$ |  $$ |$$ |         $$ |      $$ |   $$ |      $$ |  $$ |
 *    \$$$$$$  |$$$$$$$$\    $$ |      $$ |   $$$$$$$$\ $$ |  $$ |
 *     \______/ \________|   \__|      \__|   \________|\__|  \__|
 *
 */

/**
 * @brief Obtenez le nombre de chiffres dans un nombre long long.
 *
 * @param NUM: Le nombre à vérifier.
 * @return Le nombre de chiffres dans 'NUM'.
 */
int					ft_getdigits(long long NUM);

/*
 *    $$$$$$\  $$$$$$\
 *    \_$$  _|$$  __$$\
 *      $$ |  $$ /  \__|
 *      $$ |  \$$$$$$\
 *      $$ |   \____$$\
 *      $$ |  $$\   $$ |
 *    $$$$$$\ \$$$$$$  |
 *    \______| \______/
 *
 */

/**
 * @brief Vérifie si un caractère est alphanumérique.
 *
 * @param C: Le caractère à vérifier.
 * @return Non-zéro si 'C' est alphanumérique, et 0 sinon.
 */
int					ft_isalnum(int C);

/**
 * @brief Vérifie si un caractère est alphabétique.
 *
 * @param C: Le caractère à vérifier.
 * @return Non-zéro si 'C' est alphabétique, et 0 sinon.
 */
int					ft_isalpha(int C);

/**
 * @brief Vérifie si un caractère est un caractère ASCII valide.
 *
 * @param C: Le caractère à vérifier.
 * @return Non-zéro si 'C' est un caractère ASCII valide, et 0 sinon.
 */
int					ft_isascii(int C);

/**
 * @brief Vérifie si un caractère est un chiffre.
 *
 * @param C: Le caractère à vérifier.
 * @return Non-zéro si 'C' est un chiffre, et 0 sinon.
 */
int					ft_isdigit(int C);

/**
 * @brief Vérifie si un caractère est imprimable.
 *
 * @param C: Le caractère à vérifier.
 * @return Non-zéro si 'C' est imprimable, et 0 sinon.
 */
int					ft_isprint(int C);

/**
 * @brief Verifie si c'est un caractere space
 *
 * @param c
 * @return
 */
int					ft_isspace(char c);

/*
 *    $$\      $$\ $$$$$$$$\ $$\      $$\  $$$$$$\  $$$$$$$\ $$\     $$\
 *    $$$\    $$$ |$$  _____|$$$\    $$$ |$$  __$$\ $$  __$$\\$$\   $$  |
 *    $$$$\  $$$$ |$$ |      $$$$\  $$$$ |$$ /  $$ |$$ |  $$ |\$$\ $$  /
 *    $$\$$\$$ $$ |$$$$$\    $$\$$\$$ $$ |$$ |  $$ |$$$$$$$  | \$$$$  /
 *    $$ \$$$  $$ |$$  __|   $$ \$$$  $$ |$$ |  $$ |$$  __$$<   \$$  /
 *    $$ |\$  /$$ |$$ |      $$ |\$  /$$ |$$ |  $$ |$$ |  $$ |   $$ |
 *    $$ | \_/ $$ |$$$$$$$$\ $$ | \_/ $$ | $$$$$$  |$$ |  $$ |   $$ |
 *    \__|     \__|\________|\__|     \__| \______/ \__|  \__|   \__|
 *
 */

/**
 * @brief Met les premiers 'N' octets de la zone commençant à 'S' à zéro.
 *
 * @param S: Pointeur vers la zone mémoire.
 * @param N: Nombre d'octets à mettre à zéro.
 */
void				ft_bzero(void *S, size_t N);

/**
 * @brief Recherche un caractère dans un bloc de mémoire.
 *
 * @param MEMORYBLOCK: Le bloc de mémoire à analyser.
 * @param SEARCHCHAR: Le caractère à rechercher.
 * @param SIZE: La taille du bloc de mémoire.
 * @return Un pointeur vers le caractère recherché dans le bloc de mémoire,
	ou NULL si le caractère n'est pas trouvé.
 */
void				*ft_memchr(const void *MEMORYBLOCK, int SEARCHCHAR,
						size_t SIZE);

/**
 * @brief Compare les n premiers octets de deux zones de mémoire.
 *
 * @param STR1: La première zone de mémoire.
 * @param STR2: La deuxième zone de mémoire.
 * @param N: Le nombre d'octets à comparer.
 * @return Un entier inférieur, égal, ou supérieur à zéro,
	si STR1 est respectivement inférieur, égal ou supérieur à STR2.
 */
int					ft_memcmp(const void *STR1, const void *STR2, size_t N);

/**
 * @brief Copie N octets de la zone mémoire source à la zone mémoire destination
 *
 * @param DESTINATION: La zone mémoire de destination.
 * @param SOURCE: La zone mémoire source.
 * @param SIZE: Le nombre d'octets à copier.
 * @return Un pointeur vers la zone mémoire de destination.
 */
void				*ft_memcpy(void *DESTINATION, const void *SOURCE,
						size_t SIZE);

/**
 * @brief Déplace N octets de la zone mémoire à la zone mémoire destination.
 *
 * @param DESTINATION: La zone mémoire de destination.
 * @param SOURCE: La zone mémoire source.
 * @param N: Le nombre d'octets à déplacer.
 * @return Un pointeur vers la zone mémoire de destination.
 */
void				*ft_memmove(void *DESTINATION, const void *SOURCE,
						size_t N);

/**
 * @brief Remplit une zone mémoire avec un octet donné.
 *
 * @param POINTER: La zone mémoire à remplir.
 * @param VALUE: L'octet à utiliser pour remplir la zone mémoire.
 * @param SIZE: Le nombre d'octets de la zone mémoire à remplir.
 * @return Un pointeur vers la zone mémoire.
 */
void				*ft_memset(void *POINTER, int VALUE, size_t SIZE);

/**
 * @brief Alloue de la mémoire pour un tableau de N éléments de taille donnée,
	et la remplit avec des zéros.
 *
 * @param ELEMENTCOUNT: Le nombre d'éléments du tableau.
 * @param ELEMENTSIZE: La taille de chaque élément.
 * @return Un pointeur vers le tableau alloué, ou NULL si l'allocation a échoué.
 */
void				*ft_calloc(size_t ELEMENTCOUNT, size_t ELEMENTSIZE);

/**
 * @brief Change la taille de la mémoire allouée
		pointée par ptr à new_size octets.
 *
 * @param PTR: Pointeur vers la mémoire précédemment allouée avec malloc,
	calloc ou realloc à redimensionner.
 * @param OLD_SIZE: La taille actuelle de la mémoire.
 * @param NEW_SIZE: La nouvelle taille requise de la mémoire.
 * @return Un pointeur vers la mémoire nouvellement allouée,
	ou NULL si l'opération a échoué.
 */
void				*ft_realloc(void *ptr, size_t old_size, size_t new_size);

/*
 *     $$$$$$\ $$$$$$$$\ $$$$$$$\  $$$$$$\ $$\   $$\  $$$$$$\   $$$$$$\
 *    $$  __$$\\__$$  __|$$  __$$\ \_$$  _|$$$\  $$ |$$  __$$\ $$  __$$\
 *    $$ /  \__|  $$ |   $$ |  $$ |  $$ |  $$$$\ $$ |$$ /  \__|$$ /  \__|
 *    \$$$$$$\    $$ |   $$$$$$$  |  $$ |  $$ $$\$$ |$$ |$$$$\ \$$$$$$\
 *     \____$$\   $$ |   $$  __$$<   $$ |  $$ \$$$$ |$$ |\_$$ | \____$$\
 *    $$\   $$ |  $$ |   $$ |  $$ |  $$ |  $$ |\$$$ |$$ |  $$ |$$\   $$ |
 *    \$$$$$$  |  $$ |   $$ |  $$ |$$$$$$\ $$ | \$$ |\$$$$$$  |\$$$$$$  |
 *     \______/   \__|   \__|  \__|\______|\__|  \__| \______/  \______/
 */

/**
 * @brief Copie la chaîne de caractères source dans la chaîne
	de caractères destination.
 *
 * @param dest La chaîne de destination.
 * @param src La chaîne source.
 * @return Un pointeur vers la chaîne de destination.
 */
char				*ft_strcpy(char *dest, const char *src);

/**
 * @brief Recherche un caractère dans une chaîne.
 *
 * @param STR: La chaîne à analyser.
 * @param SEARCHCHAR: Le caractère à rechercher.
 * @return Un pointeur vers le caractère recherché dans la chaîne,
	ou NULL si le caractère n'est pas trouvé.
 */
char				*ft_strchr(const char *str, int searchChar);

/**
 * @brief Crée une copie de la chaîne donnée.
 *
 * @param STR: La chaîne à copier.
 * @return Un pointeur vers la nouvelle chaîne,
	ou NULL si l'allocation a échoué.
 */
char				*ft_strdup(const char *str);

/**
 * @brief Concatène deux chaînes en limitant la taille
	totale de la chaîne résultante.
 *
 * @param DESTINATION: La chaîne de destination.
 * @param SOURCE: La chaîne source.
 * @param SIZE: La taille maximale de la chaîne résultante.
 * @return La longueur totale de la chaîne qu'on aurait obtenue
	sans limite de taille.
 */
size_t				ft_strlcat(char *destination, const char *source,
						size_t size);

/**
 * @brief Concatène deux chaînes
 *
 * @param DESTINATION: La chaîne de destination.
 * @param SOURCE: La chaîne source.
 * @return Le resultat des 2 chaine concatene
 */
char				*ft_strcat(char *destination, const char *source);

/**
 * @brief Copie jusqu'à size caractères de la chaîne
	source vers la chaîne destination.
 *
 * @param DEST: La chaîne de destination.
 * @param SRC: La chaîne source.
 * @param SIZE: Le nombre maximal de caractères à copier.
 * @return La longueur de la chaîne source.
 */
size_t				ft_strlcpy(char *dest, char *src, size_t size);

/**
 * @brief Duplique une chaine de caractere jusqu'a n caractere.
 *
 * @param SRC: La chaîne a dupliquer.
 * @param SIZE: Le nombre maximal de caractères à dupliquer.
 * @return La chaine dupliquer.
 */
char				*ft_strndup(char *str, size_t size);

/**
 * @brief Duplique une chaine de caractere jusqu'a n caractere.
 *
 * @param SRC: La chaîne a dupliquer.
 * @param SIZE: Le nombre maximal de caractères à dupliquer.
 * @return La chaine dupliquer.
 */
char				*ft_strndup(char *str, size_t size);

/**
 * @brief Calcule la longueur d'une chaîne.
 *
 * @param STR: La chaîne dont on veut connaître la longueur.
 * @return La longueur de la chaîne.
 */
size_t				ft_strlen(const char *str);

/**
 * @brief Calcule la longueur d'une chaîne,
	jusqu'à un maximum de 'maxlen' caractères.
 *
 * @param str La chaîne dont on veut connaître la longueur.
 * @param maxlen Le nombre maximal de caractères à compter.
 * @return La longueur de la chaîne, jusqu'à un maximum de 'maxlen' caractères.
 */
size_t				ft_strnlen(const char *str, size_t maxlen);

/**
 * @brief Compare les 'n' premiers caractères de deux chaînes.
 *
 * @param s1 La première chaîne à comparer.
 * @param s2 La deuxième chaîne à comparer.
 * @param n Le nombre de caractères à comparer.
 * @return Un entier inférieur, égal, ou supérieur à zéro,
	si 's1' est respectivement inférieur, égal ou supérieur à 's2'.
 */
int					ft_strncmp(char *s1, char *s2, size_t n);

/**
 * @brief Compare deux chaînes.
 *
 * @param s1 La première chaîne à comparer.
 * @param s2 La deuxième chaîne à comparer.
 * @return Un entier inférieur, égal, ou supérieur à zéro,
	si 's1' est respectivement inférieur, égal ou supérieur à 's2'.
 */
int					ft_strcmp(const char *s1, const char *s2);

/**
 * @brief Recherche une sous-chaîne dans une chaîne,
	jusqu'à un maximum de 'size' caractères.
 *
 * @param source La chaîne dans laquelle effectuer la recherche.
 * @param search La sous-chaîne à rechercher.
 * @param size Le nombre maximal de caractères à analyser dans 'source'.
 * @return Un pointeur vers la première occurrence de 'search' dans 'source',
	ou NULL si 'search' n'est pas trouvé.
 */
char				*ft_strnstr(const char *source, const char *search,
						size_t size);

/**
 * @brief Recherche la dernière occurrence d'un caractère dans une chaîne.
 *
 * @param str La chaîne dans laquelle effectuer la recherche.
 * @param ch Le caractère à rechercher.
 * @return Un pointeur vers la dernière occurrence de 'ch' dans 'str',
	ou NULL si 'ch' n'est pas trouvé.
 */
char				*ft_strrchr(const char *str, int ch);

/**
 * @brief Crée une sous-chaîne de la chaîne 's',
	commençant à 'start' et de longueur 'len'.
 *
 * @param s La chaîne d'origine.
 * @param start L'indice de départ de la sous-chaîne dans 's'.
 * @param len La longueur de la sous-chaîne.
 * @return Un pointeur vers la nouvelle sous-chaîne,
	ou NULL si l'allocation a échoué.
 */
char				*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * @brief Concatène deux chaînes.
 *
 * @param s1 La première chaîne.
 * @param s2 La deuxième chaîne.
 * @return Un pointeur vers la nouvelle chaîne,
	ou NULL si l'allocation a échoué.
 */
char				*ft_strjoin(char const *s1, char const *s2);

/**
 * @brief Supprime les caractères spécifiés en début et fin de chaîne.
 *
 * @param s1 La chaîne à traiter.
 * @param set Les caractères à supprimer.
 * @return Un pointeur vers la nouvelle chaîne,
	ou NULL si l'allocation a échoué.
 */
char				*ft_strtrim(char const *s1, char const *set);

/**
 * @brief Découpe une chaîne en plusieurs chaînes à
	chaque occurrence du caractère 'c'.
 *
 * @param s La chaîne à découper.
 * @param c Le caractère délimiteur.
 * @return Un tableau de chaînes, ou NULL si l'allocation a échoué.
 */
char				**ft_split(char const *s, char c);

/**
 * @brief Découpe une chaîne en plusieurs chaînes à chaque
	occurrence du caractère 'c' et ajoute le caractere dans la liste.
 *
 * @param s La chaîne à découper.
 * @param c Le caractère délimiteur.
 * @return Un tableau de chaînes, ou NULL si l'allocation a échoué.
 */
char				**ft_split_sep(char *string, char separator);

/**
 * @brief Cherche dans une chaine de caractere si il y a le caractere 'c'.
 *
 * @param s La chaîne à analyser.
 * @param c Le caractère a chercher.
 * @return Retourne la position du caractere si il est trouver, -1 si non.
 */
int					ft_strchar(const char *string, char c);

/**
 * @brief Applique une fonction à chaque caractère de la chaîne 's'.
 *
 * @param s La chaîne à traiter.
 * @param f La fonction à appliquer à chaque caractère.
 * @return Un pointeur vers la nouvelle chaîne,
	ou NULL si l'allocation a échoué.
 */
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * @brief Applique une fonction à chaque caractère de la chaîne 's'.
 *
 * @param s La chaîne à traiter.
 * @param f La fonction à appliquer à chaque caractère.
 */
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

/**
 * @brief Inverse une chaîne de caractères.
 *
 * @param str La chaîne à inverser.
 * @return Un pointeur vers la chaîne inversée.
 */
char				*ft_strrev(char *str);

/*
 *    $$$$$$$$\  $$$$$$\
 *    \__$$  __|$$  __$$\
 *       $$ |   $$ /  $$ |
 *       $$ |   $$ |  $$ |
 *       $$ |   $$ |  $$ |
 *       $$ |   $$ |  $$ |
 *       $$ |    $$$$$$  |
 *       \__|    \______/
 */

/**
 * @brief Convertit un caractère en minuscule.
 *
 * @param c Le caractère à convertir.
 * @return Le caractère converti en minuscule.
 */

int					ft_tolower(int c);

/**
 * @brief Convertit un caractère en majuscule.
 *
 * @param c Le caractère à convertir.
 * @return Le caractère converti en majuscule.
 */
int					ft_toupper(int c);

/**
 * @brief Convertit une chaîne de caractères en un entier.
 *
 * @param str La chaîne à convertir.
 * @return L'entier résultant de la conversion.
 */
int					ft_atoi(const char *str);

/**
 * @brief Convertit un entier en une chaîne de caractères.
 *
 * @param n L'entier à convertir.
 * @return Un pointeur vers la chaîne résultant de la conversion.
 */
char				*ft_itoa(int n);

/**
 * @brief Convertit un nombre de type size_t en une chaîne
	de caractères en hexadécimal.
 *
 * @param num Le nombre à convertir.
 * @return Un pointeur vers la chaîne résultant de la conversion.
 */
char				*ft_ltoh(size_t num);

/*
 *    $$$$$$$\  $$\   $$\ $$$$$$$$\
 *    $$  __$$\ $$ |  $$ |\__$$  __|
 *    $$ |  $$ |$$ |  $$ |   $$ |
 *    $$$$$$$  |$$ |  $$ |   $$ |
 *    $$  ____/ $$ |  $$ |   $$ |
 *    $$ |      $$ |  $$ |   $$ |
 *    $$ |      \$$$$$$  |   $$ |
 *    \__|       \______/    \__|
 */

/**
 * @brief Écrit le caractère 'c' sur le descripteur de fichier donné.
 *
 * @param c Le caractère à écrire.
 * @param fd Le descripteur de fichier sur lequel écrire.
 * @return Le nombre de caractères écrits.
 */
int					ft_putchar_fd(char c, int fd);

/**
 * @brief Écrit la chaîne 's' sur le descripteur de fichier donné.
 *
 * @param s La chaîne à écrire.
 * @param fd Le descripteur de fichier sur lequel écrire.
 * @return Le nombre de caractères écrits.
 */
int					ft_putstr_fd(char *s, int fd);

/**
 * @brief Écrit la chaîne 's' et un retour à la ligne sur
	le descripteur de fichier donné.
 *
 * @param s La chaîne à écrire.
 * @param fd Le descripteur de fichier sur lequel écrire.
 * @return Le nombre de caractères écrits.
 */
int					ft_putendl_fd(char *s, int fd);

/**
 * @brief Écrit le nombre 'n' sur le descripteur de fichier donné.
 *
 * @param n Le nombre à écrire.
 * @param fd Le descripteur de fichier sur lequel écrire.
 * @return Le nombre de caractères écrits.
 */
int					ft_putnbr_fd(ssize_t n, int fd);

/**
 * @brief Écrit le nombre 'num' en hexadécimal sur le descripteur
	de fichier donné.
 *
 * @param num Le nombre à écrire.
 * @param base La base de conversion.
 * @param fd Le descripteur de fichier sur lequel écrire.
 * @return Le nombre de caractères écrits.
 */
int					ft_putptr_fd(uintptr_t num, const char *base, int fd);

/**
 * @brief Écrit le nombre 'num' en hexadécimal sur le
	descripteur de fichier donné.
 *
 * @param num Le nombre à écrire.
 * @param base La base de conversion.
 * @param fd Le descripteur de fichier sur lequel écrire.
 * @return Le nombre de caractères écrits.
 */
int					ft_puthex_fd(unsigned int num, const char *base, int fd);

/*
 *    $$\       $$$$$$\  $$$$$$\ $$$$$$$$\ $$$$$$$$\
 *    $$ |      \_$$  _|$$  __$$\\__$$  __|$$  _____|
 *    $$ |        $$ |  $$ /  \__|  $$ |   $$ |
 *    $$ |        $$ |  \$$$$$$\    $$ |   $$$$$\
 *    $$ |        $$ |   \____$$\   $$ |   $$  __|
 *    $$ |        $$ |  $$\   $$ |  $$ |   $$ |
 *    $$$$$$$$\ $$$$$$\ \$$$$$$  |  $$ |   $$$$$$$$\
 *    \________|\______| \______/   \__|   \________|
 */

/**
 * @brief Crée un nouvel élément de liste.
 *
 * @param content Le contenu du nouvel élément.
 * @return Un pointeur vers le nouvel élément de liste.
 */
t_list				*ft_lstnew(void *content);

/**
 * @brief Ajoute l'élément 'new' au début de la liste.
 *
 * @param lst Un pointeur vers le premier lien de la liste.
 * @param new L'élément à ajouter à la liste.
 */
void				ft_lstadd_front(t_list **lst, t_list *new);

/**
 * @brief Compte le nombre d'éléments de la liste.
 *
 * @param lst Le premier maillon de la liste.
 * @return Le nombre d'éléments de la liste.
 */
int					ft_lstsize(t_list *lst);

/**
 * @brief Retourne le dernier élément de la liste.
 *
 * @param lst Le premier maillon de la liste.
 * @return Le dernier élément de la liste.
 */
t_list				*ft_lstlast(t_list *lst);

/**
 * @brief Ajoute l'élément 'new' à la fin de la liste.
 *
 * @param lst Un pointeur vers le premier lien de la liste.
 * @param new L'élément à ajouter à la liste.
 */
void				ft_lstadd_back(t_list **lst, t_list *new);

/**
 * @brief Supprime un élément de la liste et libère la mémoire de l'élément.
 *
 * @param lst L'élément de la liste à supprimer.
 * @param del L'adresse de la fonction permettant de supprimer le contenu.
 */
void				ft_lstdelone(t_list *lst, void (*del)(void *));

/**
 * @brief Supprime et libère la liste.
 *
 * @param lst Un pointeur vers le premier lien de la liste.
 * @param del L'adresse de la fonction permettant de supprimer le contenu.
 */
void				ft_lstclear(t_list **lst, void (*del)(void *));

/**
 * @brief Applique une fonction à la liste 'lst'.
 *
 * @param lst La liste sur laquelle itérer.
 * @param f La fonction à appliquer à chaque élément.
 */
void				ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @brief Applique une fonction à la liste 'lst' et crée une nouvelle liste.
 *
 * @param lst La liste sur laquelle itérer.
 * @param f La fonction à appliquer à chaque élément.
 * @param del L'adresse de la fonction permettant de supprimer le contenu.
 * @return La nouvelle liste.
 */
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

#endif
