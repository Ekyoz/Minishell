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
PROJECT_NAME		= Minishell
NAME				= minishell
ARCHIVE_NAME		= $(OUT)/lib$(NAME).a
RUN_NAME			= $(NAME)
DEBUG_NAME 			= $(OUT)/debug.out
TEST_NAME			= $(OUT)/test.out

#-------- FILES --------#

HEADER_FILES		= minishell
SRC_FILES		    = main
TEST_FILES  		= test

FILE_BUILTINS_DIR 	= builtins/
FILE_BUILTINS 		= cd echo env exit export pwd unset

FILE_PARSING_DIR	= parsing/
FILE_PARSING		= parsing

DIR_LIST			= $(FILE_BUILTINS_DIR) $(FILE_PARSING_DIR)
SRC_FILES			+= $(addprefix $(FILE_BUILTINS_DIR), $(FILE_BUILTINS))
SRC_FILES			+= $(addprefix $(FILE_PARSING_DIR), $(FILE_PARSING))

#-------- LIBS --------#

LIBFT_DIR			= $(INCLUDE_DIR)/LibFT
LIBFT_ARCHIVE		= $(LIBFT_DIR)/libft.a

PIPEX_DIR			= $(INCLUDE_DIR)/Pipex
PIPEX_ARCHIVE		= $(PIPEX_DIR)/libpipex.a

LIB_LIST			= $(LIBFT_DIR) $(PIPEX_DIR)
LIB_LIST_ARCHIVE	= $(ARCHIVE_NAME) $(LIBFT_ARCHIVE) $(PIPEX_ARCHIVE)

#-------- FLAGS --------#
CFLAGS 				= -Wall -Wextra #-Werror
CFLAGS_DEBUG		= -Wall -Wextra -g3
CFLAGS_TEST			= -g3
LIBFLAGS			= -lreadline

#------------------------------------------------------------------------------#
#----------------------------- DO NOT TOUCH BELOW -----------------------------#
#------------------------------------------------------------------------------#


#-------- DIR --------#

SRC_DIR				= srcs
TEST_DIR 			= test
INCLUDE_DIR			= include
OUT					= out
SRC_OUT_DIR			= $(OUT)/run
DEBUG_OUT_DIR		= $(OUT)/debug
TEST_OUT_DIR		= $(OUT)/test
DIRS				= $(SRC_OUT_DIR) $(DEBUG_OUT_DIR) $(TEST_OUT_DIR)
HEADERS				= $(addprefix $(INCLUDE_DIR)/, $(addsuffix .h, $(HEADER_FILES)))

#-------- SETTINGS --------#

CC					= cc
OBJF				= .cache_exists
INCLUDE 			= -I$(INCLUDE_DIR) $(addprefix -I, $(addsuffix /$(INCLUDE_DIR), $(LIB_LIST)))
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

$(TEST_OUT_DIR)/%.o: $(TEST_DIR)/%.c $(HEADERS) Makefile | $(OBJF)
			@echo "$(YELLOW)$(BOLD)Compiling: $(WHITE)$< $(DEF_COLOR)"
			@$(CC) $(CFLAGS_TEST) $(INCLUDE) -c $< -o $@
			@printf "\033[A\033[K"

#-------- COMMANDS --------#

$(NAME): archive
			@$(CC) $(CFLAGS) $(OBJ) $(INCLUDE_RUN) -o $(RUN_NAME) $(LIBFLAGS)
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
			@$(CC) $(CFLAGS_DEBUG) $(OBJ_DEBUG) $(INCLUDE_RUN) -o $(DEBUG_NAME) $(LIBFLAGS)
			@echo "$(CYAN)$(BOLD)$(PROJECT_NAME)$(GREEN) a été compilé avec succès en version $(YELLOW)$(BOLD)DEBUG!$(DEF_COLOR)"

#------ TEST ------#

test: lib $(OBJ_TEST) $(HEADERS)
			@$(CC) $(CFLAGS_TEST) $(OBJ_TEST) -o $(TEST_NAME) $(LIBFLAGS)
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
			@echo "$(ORANGE)Tous les fichier objets de $(CYAN)$(BOLD)$(PROJECT_NAME)$(ORANGE) ont été supprimé!$(DEF_COLOR)"

fclean:		clean
			@echo "$(RED)Tous les fichier executable de $(CYAN)$(BOLD)$(PROJECT_NAME)$(RED) ont été supprimé!$(DEF_COLOR)\n"
			@for dir in $(LIB_LIST); do make fclean --no-print-directory -C $$dir; done
			@$(RM) $(ARCHIVE_NAME)

.PHONY:		all compile run lib re clean fclean
