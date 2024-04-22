# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atresall <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/10 12:10:27 by atresall          #+#    #+#              #
#    Updated: 2024/03/03 14:07:07 by atresall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-------- NAME --------#
PROJECT_NAME        = "Pipex"
NAME				= "pipex"
ARCHIVE_NAME		= lib$(NAME).a
RUN_NAME			= $(NAME)
DEBUG_NAME 			= $(OUT)/debug.out
TEST_NAME			= $(OUT)/test.out

#-------- FILES --------#

HEADER_FILES		= pipex
SRC_FILES		    = main checkcmd free utils
TEST_FILES  		=

DIR_LIST			= # $(FILE_UTILS_DIR) $(FILE_THREADS_DIR)
HEADERS				= $(addprefix $(INCLUDE_DIR)/, $(addsuffix .h, $(HEADER_FILES)))

#-------- DIR --------#

SRC_DIR				= srcs
TEST_DIR 			= test
INCLUDE_DIR			= include
OUT					= out
SRC_OUT_DIR			= $(OUT)/run
DEBUG_OUT_DIR		= $(OUT)/debug
TEST_OUT_DIR		= $(OUT)/test
DIRS				= $(SRC_OUT_DIR) $(DEBUG_OUT_DIR)

#-------- LIBS --------#

LIBFT_DIR			= $(INCLUDE_DIR)/LibFt
LIBFT_ARCHIVE		= $(LIBFT_DIR)/libft.a

LIB_LIST			= $(LIBFT_DIR)
LIB_LIST_ARCHIVE	= $(ARCHIVE_NAME) $(LIBFT_ARCHIVE)

#-------- SETTINGS --------#

CC					= cc
CFLAGS 				= -Wall -Werror -Wextra -pthread
CFLAGS_DEBUG		= -Wall -Wextra -pthread -g3
CFLAGS_TEST			= -g3
OBJF				= .cache_exists
INCLUDE 			= -I$(INCLUDE_DIR) -I$(LIBFT_DIR)/$(INCLUDE_DIR)
INCLUDE_RUN			= -L. $(ARCHIVE_NAME)
RM					= rm -rf
AR					= ar rcs

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
			@mkdir -p $(SRC_OUT_DIR)
			@mkdir -p $(DEBUG_OUT_DIR)
			@mkdir -p $(TEST_OUT_DIR)
			@for dirs in $(DIRS); do \
                    for dir in $(DIR_LIST); do \
                        mkdir -p $$dirs/$$dir; \
                    done; \
                done


$(SRC_OUT_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) Makefile | $(OBJF)
			@echo "$(YELLOW)$(BOLD)Compiling: $(WHITE)$< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
			@printf "\033[A\033[K"

$(DEBUG_OUT_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) Makefile | $(OBJF)
			@echo "$(YELLOW)$(BOLD)Compiling: $(WHITE)$< $(DEF_COLOR)"
			@$(CC) $(CFLAGS_DEBUG) $(INCLUDE) -c $< -o $@
			@printf "\033[A\033[K"

$(TEST_OUT_DIR)/%.o: $(TEST_FILES)/%.c $(HEADERS) Makefile | $(OBJF)
			@echo "$(YELLOW)$(BOLD)Compiling: $(WHITE)$< $(DEF_COLOR)"
			@$(CC) $(CFLAGS_TEST) $(INCLUDE) -c $< -o $@
			@printf "\033[A\033[K"

#-------- COMMANDS --------#

$(NAME): archive
			@echo "$(CYAN)$(BOLD)$(PROJECT_NAME)$(GREEN) a été compilé avec succès!$(DEF_COLOR)"

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

#------- DEBUG --------#

ar_debug:	lib $(OBJ_DEBUG) $(HEADERS)
			@$(AR) $(ARCHIVE_NAME) $(OBJ_DEBUG)
			@for archive in $(LIB_LIST_ARCHIVE); do ar -x $$archive; done
			@ar -qcs $(ARCHIVE_NAME) *.o
			@$(RM) *.o
			@$(RM) __.*

debug: ar_debug
			@$(CC) $(CFLAGS_DEBUG) $(OBJ_DEBUG) $(INCLUDE_RUN) -o $(DEBUG_NAME)
			@echo "$(CYAN)$(BOLD)$(PROJECT_NAME)$(GREEN) a été compilé avec succès en version $(YELLOW)$(BOLD)DEBUG!$(DEF_COLOR)"

#------ TEST ------#

ar_test:	lib $(OBJ_TEST) $(HEADERS)
			@$(AR) $(ARCHIVE_NAME) $(OBJ_DEBUG)
			@for archive in $(LIB_LIST_ARCHIVE); do ar -x $$archive; done
			@ar -qcs $(ARCHIVE_NAME) *.o
			@$(RM) *.o
			@$(RM) __.*

test: ar_debug ar_test
			@$(CC) $(CFLAGS_TEST) $(OBJ_TEST) $(INCLUDE_RUN) -o $(TEST_NAME)
			@echo "$(CYAN)$(BOLD)$(PROJECT_NAME)$(GREEN) a été compilé avec succès en version $(YELLOW)$(BOLD)TEST!$(DEF_COLOR)"

#-------- CLEAN --------#
re:			fclean $(NAME)
			@echo "$(GREEN)Nettoyage et recompilage de $(PROJECT_NAME)!$(DEF_COLOR)"

clean:
			@$(RM) $(SRC_OUT_DIR)
			@$(RM) $(DEBUG_OUT_DIR)
			@$(RM) $(OUT)
			@$(RM) $(RUN_NAME)
			@$(RM) $(DEBUG_NAME)
			@$(RM) *.o
			@$(RM) __.*
			@$(RM) output outfile infile input
			@echo "$(ORANGE)Tous les fichier objets de $(CYAN)$(BOLD)$(PROJECT_NAME)$(ORANGE) ont été supprimé!$(DEF_COLOR)"

fclean:		clean
			@echo "$(RED)Tous les fichier executable de $(CYAN)$(BOLD)$(PROJECT_NAME)$(RED) ont été supprimé!$(DEF_COLOR)\n"
			@for dir in $(LIB_LIST); do make fclean --no-print-directory -C $$dir; done
			@$(RM) $(ARCHIVE_NAME)

.PHONY:		all compile run lib re clean fclean
