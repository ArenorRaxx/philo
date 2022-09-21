# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/12 08:34:12 by mcorso            #+#    #+#              #
#    Updated: 2022/09/20 15:35:20 by mcorso           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo

#	Source files
SRC_FILES		=	args_manager.c \
					deth_manager.c \
					error.c \
					fork_manager.c \
					log_manager.c \
					mutex_manager.c\
					philo_eats_action.c \
					philo_manager.c \
					philo_sleeps_action.c \
					philo_thinks_action.c\
					philo.c

SRCS			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS			=	$(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

#	Directory
HEAD			=	./
SRC_DIR			=	./srcs/
OBJ_DIR			=	./objs/

#	Compiler
CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra
INC_THREAD		=	-lpthread

all				:	obj $(NAME)

obj				:
					mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c
					$(CC) $(CFLAGS) -I$(HEAD) -o $@ -c $<

$(NAME)			:	$(OBJS)
					$(CC) $(OBJS) -o $(NAME) $(INC_THREAD)

clean			:	
					rm -rf $(OBJ_DIR)

fclean			:	clean
					rm -rf $(NAME)

re				:	fclean all

.PHONY			:	all obj $(NAME) clean fclean re