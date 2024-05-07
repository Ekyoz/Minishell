# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atresall <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/10 12:10:27 by atresall          #+#    #+#              #
#    Updated: 2024/03/03 13:45:53 by atresall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-------- NAME --------#
PROJECT_NAME 	= "LibFt"
NAME			= ft
ARCHIVE_NAME	= lib$(NAME).a
RUN_NAME		= $(OUT_DIR)/$(NAME).out	
TEST_NAME 		= $(OUT_DIR)/test.out

#-------- FILES --------#

FILE_GET_DIR = get/
FILE_GET = ft_getdigits

FILE_IS_DIR	=	is/
FILE_IS		=	ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint

FILE_LST_DIR	=	lst/
FILE_LST		=	ft_lstadd_back_bonus ft_lstadd_front_bonus ft_lstclear_bonus ft_lstdelone_bonus \
				ft_lstiter_bonus ft_lstlast_bonus ft_lstmap_bonus ft_lstnew_bonus ft_lstsize_bonus

FILE_MEM_DIR	=	mem/
FILE_MEM		=	ft_bzero ft_calloc ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset ft_realloc

FILE_PUT_DIR	=	put/
FILE_PUT		=	ft_putchar_fd ft_putendl_fd ft_puthex_fd ft_putnbr_fd ft_putptr_fd ft_putstr_fd

FILE_STR_DIR	=	str/
FILE_STR		=	ft_split ft_strchr ft_strdup ft_striteri ft_strjoin \
				ft_strlcat ft_strlcpy ft_strlen ft_strmapi ft_strncmp \
				ft_strnstr ft_strrchr ft_strrev ft_strtrim ft_substr ft_strnlen ft_strcmp ft_strchar ft_split_sep ft_strcpy ft_strlen_array
				
FILE_TO_DIR	=	to/
FILE_TO		=	ft_atoi ft_itoa ft_ltoh ft_tolower ft_toupper

SRC_FILES+=$(addprefix $(FILE_GET_DIR),$(FILE_GET))
SRC_FILES+=$(addprefix $(FILE_IS_DIR),$(FILE_IS))
SRC_FILES+=$(addprefix $(FILE_LST_DIR),$(FILE_LST))
SRC_FILES+=$(addprefix $(FILE_MEM_DIR),$(FILE_MEM))
SRC_FILES+=$(addprefix $(FILE_PUT_DIR),$(FILE_PUT))
SRC_FILES+=$(addprefix $(FILE_STR_DIR),$(FILE_STR))
SRC_FILES+=$(addprefix $(FILE_TO_DIR),$(FILE_TO))

TEST_FILES  = main

#-------- DIR --------#

SRC_DIR			= srcs
INCLUDE_DIR		= include
OUT_DIR			= out
TEST_DIR 		= test

#-------- LIBS --------#

LIB_LIST			= 
LIB_LIST_ARCHIVE	= 


#-------- SETTINGS --------#

CC				= gcc
ifeq ($(FLAGS),1)
    CFLAGS = 								#Flags for tests
else
    CFLAGS = -Wall -Werror -Wextra			#Flags for run
endif
OBJF			=	.cache_exists
INCLUDE 		= -I$(INCLUDE_DIR) 
INCLUDE_RUN		= -L. $(ARCHIVE_NAME)
RM				= rm -f
AR				= ar rcs

#-------- COLORS --------#

DEF_COLOR 	= \033[0;39m
GREEN 		= \033[0;92m
YELLOW 		= \033[0;93m
BLUE 		= \033[0;94m
CYAN 		= \033[0;96m
RED 		= \033[0;31m
ORANGE 		= \033[0;33m
WHITE		= \033[0;00m
BOLD		= \033[1m

#-------- OBJECTS --------#

OBJ 		= 	$(addprefix $(OUT_DIR)/, $(addsuffix .o, $(SRC_FILES)))
OBJ_RUN 		= 	$(addprefix $(OUT_DIR)/, $(addsuffix .o, $(TEST_FILES)))

#-------- COMMANDS VARIABLE--------#

#--- Compiling objects ---#
$(OUT_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJF)
			@echo "$(YELLOW)$(BOLD)Compiling: $(WHITE)$< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
			@printf "\033[A\033[K"
			
#--- Compiling test objects ---#
$(OUT_DIR)/%.o: $(TEST_DIR)/%.c | $(OBJF)
			@echo "$(YELLOW)$(BOLD)Compiling: $(WHITE)$< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
			@printf "\033[A\033[K"


$(ARCHIVE_NAME):	lib $(OBJ)
			@$(AR) $(ARCHIVE_NAME) $(OBJ)
			@for archive in $(LIB_LIST_ARCHIVE); do ar -x $$archive; done
			@ar -qcs $(ARCHIVE_NAME) $(OBJ)
			@rm -f *.o	
			@rm -f __.*
			@echo "$(CYAN)$(BOLD)$(PROJECT_NAME)$(GREEN) a été compilé avec succès!$(DEF_COLOR)"

$(OBJF):
			@mkdir -p $(OUT_DIR)
			@mkdir -p $(OUT_DIR)/$(FILE_GET_DIR)
			@mkdir -p $(OUT_DIR)/$(FILE_IS_DIR)
			@mkdir -p $(OUT_DIR)/$(FILE_LST_DIR)
			@mkdir -p $(OUT_DIR)/$(FILE_MEM_DIR)
			@mkdir -p $(OUT_DIR)/$(FILE_PUT_DIR)
			@mkdir -p $(OUT_DIR)/$(FILE_STR_DIR)
			@mkdir -p $(OUT_DIR)/$(FILE_TO_DIR)

#-------- COMMANDS --------#

all:		$(ARCHIVE_NAME)

compile: all $(OBJ_RUN)
	@$(CC) $(CFLAGS) $(OBJ_RUN) $(INCLUDE_RUN) -o $(RUN_NAME)

run: compile
	./$(RUN_NAME)

lib:
			@for dir in $(LIB_LIST); do make --no-print-directory -C $$dir; done

re:			fclean all
			@echo "$(GREEN)Nettoyage et recompilage de $(PROJECT_NAME)!$(DEF_COLOR)"

#-------- CLEAN --------#

clean:
			@$(RM) -rf $(OUT_DIR)
			@rm -f *.o	
			@rm -f __.*
			@echo "$(ORANGE)Tous les fichier objets de $(CYAN)$(BOLD)$(PROJECT_NAME)$(ORANGE) ont été supprimé!$(DEF_COLOR)"

fclean:		clean
			@echo "$(RED)Tous les fichier executable de $(CYAN)$(BOLD)$(PROJECT_NAME)$(RED) ont été supprimé!$(DEF_COLOR)\n"
			@for dir in $(LIB_LIST); do make fclean --no-print-directory -C $$dir; done
			@$(RM) -f $(ARCHIVE_NAME)
			@$(RM) -f $(TEST_NAME)

.PHONY:		all compile run lib re clean fclean