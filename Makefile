##
## EPITECH PROJECT, 2022
## B-MUL-200-MPL-2-1-mydefender-hippolyte.aubert
## File description:
## Makefile
##

################### Color ########################
BLUE			=	/bin/echo -e "\x1b[34;01m$1\x1b[0m"
GREEN			=	/bin/echo -e "\x1b[32;01m$1\x1b[0m"

#################### Make ########################
#MAKE_LIB		=	make -C lib/my/ -s

CC			=	@gcc
CFLAGS		=	-I./ -g
DEBUG		=	-g3

#################### Rules #######################
SRC		=	$(wildcard *.c) \
			$(wildcard cd/*.c) \
			$(wildcard env/*.c) \
			$(wildcard execute/*.c) \
			$(wildcard lib/*.c) \
			$(wildcard parsing/*.c) \
			$(wildcard redirection/*.c) \
			$(wildcard error_handle/*.c)

OBJ		=	$(SRC:.c=.o)

BIN		=	mysh

all:	$(OBJ)
#@$(MAKE_LIB)
		@$(CC) $(CFLAGS) $(OBJ) -o $(BIN)
		@$(call BLUE,"Build [OK] 🏗️")
		@$(call GREEN,"Minishell1 [OK] 👨‍💻")

clean:
	@rm -rf $(OBJ)
#@$(MAKE_LIB) clean

fclean: clean
	@rm -f $(BIN)
	@$(call BLUE,"Fclean [OK] 🧹")
#@$(MAKE_LIB) fclean

re: fclean all

################# My Commands ####################
g3:
	$(eval CFLAGS += $(DEBUG))
	@$(call BLUE,"Build -g3 [OK] 🔎")

my: re clean

##SRC		=	$(wildcard *.c)
