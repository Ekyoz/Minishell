# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atresall <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/10 12:10:27 by atresall          #+#    #+#              #
#    Updated: 2023/12/20 13:01:49 by atresall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-------- NAME --------#
PROJECT_NAME 	= "Get Next Line"
NAME			= gnl
ARCHIVE_NAME	= lib$(NAME).a
RUN_NAME		= $(OUT_DIR)/$(NAME).out	
TEST_NAME 		= $(OUT_DIR)/test.out

#-------- FILES --------#

SRC_FILES	= get_next_line get_next_line_utils
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
COUNTER				= 0

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
			$(eval COUNTER=$(shell expr $(COUNTER) + 1))
			
#--- Compiling test objects ---#
$(OUT_DIR)/%.o: $(TEST_DIR)/%.c | $(OBJF)
			@echo "$(YELLOW)$(BOLD)Compiling: $(WHITE)$< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
			@printf "\033[A\033[K"
			$(eval COUNTER=$(shell expr $(COUNTER) + 1))


$(ARCHIVE_NAME):	lib $(OBJ)
			@$(AR) $(ARCHIVE_NAME) $(OBJ)
			@for archive in $(LIB_LIST_ARCHIVE); do ar -x $$archive; done
			@ar -qcs $(ARCHIVE_NAME) $(OBJ)
			@rm -f *.o	
			@rm -f __.*
			@echo "$(CYAN)$(BOLD)$(PROJECT_NAME)$(GREEN) a été compilé avec succès!$(DEF_COLOR) ($(YELLOW)$(BOLD)$(COUNTER)$(DEF_COLOR) $(WHITE)fichiers$(DEF_COLOR))"


$(OBJF):
			@mkdir -p $(OUT_DIR)

#-------- COMMANDS --------#

all:		$(ARCHIVE_NAME)

compile: all $(OBJ_RUN)
	@$(CC) $(CFLAGS) $(OBJ_RUN) $(INCLUDE_RUN) -o $(RUN_NAME)

run: compile
	./$(RUN_NAME)

lib:
			@for dir in $(LIB_LIST); do make -C $$dir; done

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
			@for dir in $(LIB_LIST); do make fclean -C $$dir; done
			@$(RM) -f $(ARCHIVE_NAME)
			@$(RM) -f $(TEST_NAME)

.PHONY:		all compile run lib re clean fclean