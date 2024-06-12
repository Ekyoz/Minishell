# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bpoyet <bpoyet@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/10 12:10:27 by atresall          #+#    #+#              #
#    Updated: 2024/06/06 19:25:32 by bpoyet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-------- NAME --------#
PROJECT_NAME		= "LibFt"
NAME				= "ft"

#-------- FILES --------#

HEADER_FILES			= libft
SRC_FILES		    	=
TEST_FILES  			=

FILE_GET_DIR			= 	get/
FILE_GET				= 	ft_getdigits

FILE_IS_DIR				=	is/
FILE_IS					=	ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint ft_isspace

FILE_LST_DIR			=	lst/
FILE_LST				=	ft_lstadd_back_bonus ft_lstadd_front_bonus ft_lstclear_bonus ft_lstdelone_bonus \
							ft_lstiter_bonus ft_lstlast_bonus ft_lstmap_bonus ft_lstnew_bonus ft_lstsize_bonus

FILE_MEM_DIR			=	mem/
FILE_MEM				=	ft_bzero ft_calloc ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset ft_realloc

FILE_PUT_DIR			=	put/
FILE_PUT				=	ft_putchar_fd ft_putendl_fd ft_puthex_fd ft_putnbr_fd ft_putptr_fd ft_putstr_fd

FILE_STR_DIR			=	str/
FILE_STR				=	ft_split ft_strchr ft_strdup ft_striteri ft_strjoin \
							ft_strlcat ft_strlcpy ft_strlen ft_strmapi ft_strncmp \
							ft_strnstr ft_strrchr ft_strrev ft_strtrim ft_substr \
							ft_strnlen ft_strcmp ft_strchar ft_split_sep ft_strcpy \
							ft_strcat ft_strndup

FILE_TO_DIR				=	to/
FILE_TO					=	ft_atoi ft_itoa ft_ltoh ft_tolower ft_toupper

FILE_ARRAY_DIR 			=	arrays/
FILE_ARRAY				=	ft_arradd ft_arrlen ft_arrdup ft_arrdel

DIR_LIST				= $(FILE_GET_DIR) $(FILE_IS_DIR) $(FILE_LST_DIR) $(FILE_MEM_DIR) $(FILE_PUT_DIR) $(FILE_STR_DIR) $(FILE_TO_DIR) $(FILE_ARRAY_DIR)

SRC_FILES+=$(addprefix $(FILE_GET_DIR),$(FILE_GET))
SRC_FILES+=$(addprefix $(FILE_IS_DIR),$(FILE_IS))
SRC_FILES+=$(addprefix $(FILE_LST_DIR),$(FILE_LST))
SRC_FILES+=$(addprefix $(FILE_MEM_DIR),$(FILE_MEM))
SRC_FILES+=$(addprefix $(FILE_PUT_DIR),$(FILE_PUT))
SRC_FILES+=$(addprefix $(FILE_STR_DIR),$(FILE_STR))
SRC_FILES+=$(addprefix $(FILE_TO_DIR),$(FILE_TO))
SRC_FILES+=$(addprefix $(FILE_ARRAY_DIR),$(FILE_ARRAY))


#-------- LIBS --------#

LIB_LIST			=
LIB_LIST_ARCHIVE	= $(ARCHIVE_NAME)

#-------- FLAGS --------#
CFLAGS 				= -Wall -Wextra -Werror -g3
CFLAGS_DEBUG		= -Wall -Wextra -g3
CFLAGS_EXEC			= -Wall -Wextra -Werror -g3
CFLAGS_PARSING		= -Wall -Wextra -Werror -g3
CFLAGS_TEST			= -g3
INCLUDES			=
LIBFLAGS			=
VFALGS				= -s --leak-check=full --track-origins=yes --suppressions=supp.supp --show-leak-kinds=all

#------------------------------------------------------------------------------#
#----------------------------- DON'T TOUCH BELOW -----------------------------#
#------------------------------------------------------------------------------#

#-------- NAMES --------#
ARCHIVE_NAME		= lib$(NAME).a
RUN_NAME			= $(NAME)
DEBUG_NAME 			= $(OUT)/debug.out
TEST_NAME			= $(OUT)/test.out

#-------- DIR --------#

SRC_DIR				= srcs
TEST_DIR 			= test
INCLUDE_DIR			= include
OUT					= .objs

#----RULES DIRS----#
SRC_OUT_DIR			= $(OUT)/run
DEBUG_OUT_DIR		= $(OUT)/debug
TEST_OUT_DIR		= $(OUT)/test

DIRS				= $(SRC_OUT_DIR) $(DEBUG_OUT_DIR) $(TEST_OUT_DIR)
HEADERS				= $(addprefix $(INCLUDE_DIR)/, $(addsuffix .h, $(HEADER_FILES)))

#-------- SETTINGS --------#

CC					= cc
OBJF				= .cache_exists
INCLUDE 			= $(INCLUDES) -I$(INCLUDE_DIR) $(addprefix -I, $(addsuffix /$(INCLUDE_DIR), $(LIB_LIST)))
INCLUDE_RUN			= -L. $(ARCHIVE_NAME)
RM					= rm -rf
AR					= ar rcs
COUNTER				= 0

#-------- COLORS --------#

DEF_COLOR 			= \033[0;39m
GREEN 				= \033[0;92m
YELLOW 				= \033[0;93m
BLUE 				= \033[0;94m
CYAN 				= \033[0;96m
RED 				= \033[0;31m
ORANGE 				= \033[0;33m
WHITE				= \033[0;00m
BOLD				= \033[1m

#-------- OBJECTS RUN --------#

OBJ			 		= $(addprefix $(SRC_OUT_DIR)/, $(addsuffix .o, $(SRC_FILES)))
OBJ_DEBUG			= $(addprefix $(DEBUG_OUT_DIR)/, $(addsuffix .o, $(SRC_FILES)))
OBJ_TEST			= $(addprefix $(TEST_OUT_DIR)/, $(addsuffix .o, $(TEST_FILES)))

$(OBJF):
			@mkdir -p $(DIRS)
			@for dirs in $(DIRS); do \
                    for dir in $(DIR_LIST); do \
                        mkdir -p $$dirs/$$dir; \
                    done; \
                done


define compile_object
			@echo "$(YELLOW)$(BOLD)Compiling: $(WHITE)$< $(DEF_COLOR)"
			@$(CC) $(1) $(INCLUDE) -c $< -o $@
			@printf "\033[A\033[K"
			@touch $@.updated
			$(eval COUNTER=$(shell expr $(COUNTER) + 1))
endef

$(SRC_OUT_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) Makefile | $(OBJF)
			$(call compile_object,$(CFLAGS))

$(DEBUG_OUT_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) Makefile | $(OBJF)
			$(call compile_object,$(CFLAGS_DEBUG))

$(TEST_OUT_DIR)/%.o: $(TEST_DIR)/%.c $(HEADERS) Makefile | $(OBJF)
			$(call compile_object,$(CFLAGS_TEST))

#-------- COMMANDS --------#

$(NAME): archive $(OBJ) $(HEADERS)
			@files=$$(find $(OUT) -name '*.updated'); \
			if [ -n "$$files" ]; then \
				echo "$(CYAN)$(BOLD)$(PROJECT_NAME)$(GREEN) a été compilé avec succès!$(DEF_COLOR) ($(YELLOW)$(BOLD)$(COUNTER)$(DEF_COLOR) $(WHITE)fichiers$(DEF_COLOR))"; \
				rm -f $$files; \
			else \
				echo "$(CYAN)$(BOLD)$(PROJECT_NAME)$(GREEN) est déjà à jour!$(DEF_COLOR)"; \
			fi

all: $(NAME)

lib:
			@for dir in $(LIB_LIST); do make --no-print-directory -C $$dir; done

#-------- RUN ---------#

archive:	lib $(OBJ) $(HEADERS)
			@$(AR) $(ARCHIVE_NAME) $(OBJ)
			@for archive in $(LIB_LIST_ARCHIVE); do ar -x $$archive; done
			@ar -qcs $(ARCHIVE_NAME) *.o
			@rm -rf *.o
			@rm -rf __.*

run: $(NAME)
			./$(RUN_NAME)

valgrind: $(NAME)
			valgrind $(VFALGS) ./$(RUN_NAME)

#------- DEBUG --------#

ar_debug:	lib $(OBJ_DEBUG) $(HEADERS)
			@$(AR) $(ARCHIVE_NAME) $(OBJ_DEBUG)
			@for archive in $(LIB_LIST_ARCHIVE); do ar -x $$archive; done
			@ar -qcs $(ARCHIVE_NAME) *.o
			@$(RM) *.o
			@$(RM) __.*

debug: ar_debug
			@$(CC) $(CFLAGS_DEBUG) $(OBJ_DEBUG) $(INCLUDE_RUN) -o $(DEBUG_NAME) $(LIBFLAGS)
			@echo "$(CYAN)$(BOLD)$(PROJECT_NAME)$(GREEN) a été compilé avec succès en version $(YELLOW)$(BOLD)DEBUG!$(DEF_COLOR)"

#------ TEST ------#

ar_test:	lib $(OBJ_TEST) $(HEADERS)
			@$(AR) $(ARCHIVE_NAME) $(OBJ_TEST)
			@for archive in $(LIB_LIST_ARCHIVE); do ar -x $$archive; done
			@ar -qcs $(ARCHIVE_NAME) *.o
			@$(RM) *.o
			@$(RM) __.*

test: ar_test
			@$(CC) $(CFLAGS_TEST) $(OBJ_TEST) $(INCLUDE_RUN) -o $(TEST_NAME) $(LIBFLAGS)
			@echo "$(CYAN)$(BOLD)$(PROJECT_NAME)$(GREEN) a été compilé avec succès en version $(YELLOW)$(BOLD)TEST!$(DEF_COLOR)"

#-------- CLEAN --------#
re:			fclean all
			@echo "$(GREEN)Nettoyage et recompilage de $(PROJECT_NAME)!$(DEF_COLOR)"
			./$(RUN_NAME)

clean:
			@$(RM) $(DIRS)
			@$(RM) $(OUT)
			@$(RM) $(RUN_NAME)
			@$(RM) $(DEBUG_NAME)
			@$(RM) $(TEST_NAME)
			@$(RM) *.o
			@$(RM) __.*
			@echo "$(ORANGE)Tous les fichier objets de $(CYAN)$(BOLD)$(PROJECT_NAME)$(ORANGE) ont été supprimé!$(DEF_COLOR)"

fclean:		clean
			@echo "$(RED)Tous les fichier executable de $(CYAN)$(BOLD)$(PROJECT_NAME)$(RED) ont été supprimé!$(DEF_COLOR)\n"
			@for dir in $(LIB_LIST); do make fclean --no-print-directory -C $$dir; done
			@$(RM) $(ARCHIVE_NAME)

.PHONY:		all compile run archive valgrind ar_debug debug ar_test test lib re clean fclean
