# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bastpoy <bastpoy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/10 12:10:27 by atresall          #+#    #+#              #
#    Updated: 2024/06/21 14:29:35 by bastpoy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-------- NAME --------#
PROJECT_NAME		= Minishell
NAME				= minishell

#-------- FILES --------#

HEADER_FILES			= minishell
SRC_FILES		    	= main
TEST_FILES  			= test

#-------- BUILTINS --------#
FILE_BUILTINS_DIR 		= builtins/
FILE_BUILTINS 			= cd echo env exit pwd unset builtin

FILE_EXPORT_DIR			= builtins/export/
FILE_EXPORT 			= export_check export

#-------- EXEC --------#
FILE_EXEC_DIR			= exec/
FILE_EXEC				= command exec exec1 exec2 exec3 heredoc heredoc_utils heredoc_utils1 pipe fork utils_pipe

#-------- AST --------#
FILE_AST_DIR			= ast/
FILE_AST				= create_ast nodes token_type tree

#-------- GARBAGE --------#
FILE_GARBAGE_DIR		= garbage_collector/
FILE_GARBAGE			= error error1 status_code free_tree free_tree1 free_twodim_array

#-------- REDIRECTION --------#
FILE_REDIRECTION_DIR 	= redirection/
FILE_REDIRECTION		= testopenredir redirec

#-------- SIGNALS --------#
FILE_SIGNAL_DIR			= signal/
FILE_SIGNAL 			= signal_cmd signal_heredoc signal

#-------- PARSING --------#
FILE_PARSING_DIR		= parsing/
FILE_PARSING			= parsing token pipe redir splitter

FILE_PARS_UTILS_DIR		= parsing/utils/
FILE_PARS_UTILS			= parser token pipe check_space free_chars parsing

FILE_PARS_QUOTE_DIR		= parsing/quote/
FILE_PARS_QUOTE			= quote quote_1 quote_2 quote_3 quote_string

FILE_PARS_EXPAND_DIR	= parsing/expand/
FILE_PARS_EXPAND		= expand expand_1 expand_array expand_string

FILE_PARS_CHECKER_DIR	= parsing/checker/
FILE_PARS_CHECKER		= checker

DIR_LIST			= $(FILE_BUILTINS_DIR) $(FILE_PARSING_DIR) $(FILE_EXEC_DIR)\
					 $(FILE_AST_DIR) $(FILE_GARBAGE_DIR) $(FILE_REDIRECTION_DIR)\
					 $(FILE_PARS_UTILS_DIR) $(FILE_SIGNAL_DIR) $(FILE_EXPORT_DIR)\
					 $(FILE_PARS_QUOTE_DIR) $(FILE_PARS_CHECKER_DIR) $(FILE_PARS_EXPAND_DIR)

SRC_FILES			+= $(addprefix $(FILE_BUILTINS_DIR), $(FILE_BUILTINS))
SRC_FILES			+= $(addprefix $(FILE_PARSING_DIR), $(FILE_PARSING))
SRC_FILES			+= $(addprefix $(FILE_PARS_UTILS_DIR), $(FILE_PARS_UTILS))
SRC_FILES			+= $(addprefix $(FILE_PARS_QUOTE_DIR), $(FILE_PARS_QUOTE))
SRC_FILES			+= $(addprefix $(FILE_PARS_CHECKER_DIR), $(FILE_PARS_CHECKER))
SRC_FILES			+= $(addprefix $(FILE_EXEC_DIR), $(FILE_EXEC))
SRC_FILES			+= $(addprefix $(FILE_EXPORT_DIR), $(FILE_EXPORT))
SRC_FILES			+= $(addprefix $(FILE_AST_DIR), $(FILE_AST))
SRC_FILES			+= $(addprefix $(FILE_GARBAGE_DIR), $(FILE_GARBAGE))
SRC_FILES			+= $(addprefix $(FILE_REDIRECTION_DIR), $(FILE_REDIRECTION))
SRC_FILES			+= $(addprefix $(FILE_SIGNAL_DIR), $(FILE_SIGNAL))
SRC_FILES			+= $(addprefix $(FILE_PARS_EXPAND_DIR), $(FILE_PARS_EXPAND))


#-------- LIBS --------#

LIBFT_DIR			= $(INCLUDE_DIR)/LibFT
LIBFT_ARCHIVE		= $(LIBFT_DIR)/libft.a

GNL_DIR				= $(INCLUDE_DIR)/GNL
GNL_ARCHIVE			= $(GNL_DIR)/libgnl.a

LIB_LIST			= $(LIBFT_DIR) $(GNL_DIR)
LIB_LIST_ARCHIVE	= $(ARCHIVE_NAME) $(LIBFT_ARCHIVE) $(GNL_ARCHIVE)

#-------- FLAGS --------#
CFLAGS 				= -Wall -Wextra -g3
CFLAGS_DEBUG		= -Wall -Wextra -g3
CFLAGS_EXEC			= -Wall -Wextra -g3 -Werror
CFLAGS_PARSING		= -Wall -Wextra -g3 -Werror
CFLAGS_TEST			= -g3
INCLUDES			= -I/opt/homebrew/opt/readline/include
LIBFLAGS			= -L/opt/homebrew/opt/readline/lib -lreadline
VFALGS				= -s --leak-check=full --track-origins=yes --suppressions=supp.supp --show-leak-kinds=all

#------------------------------------------------------------------------------#
#----------------------------- DON'T TOUCH BELOW -----------------------------#
#------------------------------------------------------------------------------#

#-------- NAMES --------#
ARCHIVE_NAME		= $(OUT)/lib$(NAME).a
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
				$(CC) $(CFLAGS) $(OBJ) $(INCLUDE_RUN) -o $(RUN_NAME) $(LIBFLAGS); \
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

valgrind: debug
			valgrind $(VFALGS) ./$(DEBUG_NAME)

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
