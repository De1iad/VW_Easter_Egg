# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 20:17:58 by libacchu          #+#    #+#              #
#    Updated: 2023/03/01 21:49:13 by obibby           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	create_file
OBJ_DIR =	obj/
SRC_DIR =	src/
SRC		=	transform.c WavLib.c FftLib.c output_to_file.c
INC		=	inc/EasterEgg.h inc/FftLib.h inc/WavLib.h
SYS		=	$(shell uname -s)
ifeq ($(SYS), Linux)
    LIBS    =	-lfftw3 -lm -lrt
else
	LIBS    =	-lfftw3 -lm
endif
SRCS	=	$(addprefix $(SRC_DIR), $(SRC))
OBJ		=	$(SRCS:%.c=$(OBJ_DIR)%.o)
CC		=	gcc
#CFLAGS	=	-Wall -Wextra -Werror
CFLAGS	=	-DDEBUG
GREY	=	\33[1;30m
BLUE	=	\33[0;34m
DEFLT	=	\33[0m
RESET	=	\33[2K

all : $(NAME)

$(OBJ_DIR)%.o : %.c
	@mkdir -p $(@D)
	@printf "$(RESET)\r$(GREY)Compiling $(BLUE)$<"
	@$(CC) $(CFLAGS) -c -g $< -o $@

$(NAME) : $(OBJ) $(INC)
	@printf "\n"
	@$(COPY)
	@printf "$(RESET)\r$(GREY)Compiling $(BLUE)$(NAME)$(DEFLT)\n"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

clean :
	@printf "$(GREY)Removing $(BLUE)$(OBJ)$(DEFLT)\n"
	@rm -fr $(OBJ_DIR)

fclean : clean
	@printf "$(GREY)Removing $(BLUE)$(NAME)$(DEFLT)\n"
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re