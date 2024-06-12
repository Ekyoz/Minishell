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
PROJECT_NAME		= "Get Next Line"
NAME				= "gnl"

#-------- FILES --------#

HEADER_FILES			=
SRC_FILES		    	= get_next_line get_next_line_utils
TEST_FILES  			=

LIB_LIST				=
LIB_LIST_ARCHIVE		= $(ARCHIVE_NAME)

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
			@if [ -z "$(ARG)" ]; then \
					./$(RUN_NAME); \
				else \
					./$(RUN_NAME) $(ARG); \
				fi

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
