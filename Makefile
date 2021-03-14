# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rburton <rburton@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/28 11:32:38 by rburton           #+#    #+#              #
#    Updated: 2021/01/28 14:12:46 by rburton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC 		= 	mlx_test.c \

OBJS		= ${SRC:.c=.o}

NAME		= test

GCC			= gcc

CFLAGS		= -g -Wall -Wextra -Werror
#CFLAGS		= -g

MLXDY		= make -C ./mlx_dy/

OPENGL		= -framework OpenGL -framework AppKit

RM			= rm -f

FT_H		= mlx_test.h

LIB			= libmlx.dylib

all:	${NAME}

#bonus:	all

#сопоставление *.c и *.o файлов
.c.o:
		${GCC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:		${OBJS} ${HEADER}
				# ${MLXST}
				# cp ./mlx_st/libmlx.a .
				${MLXDY}
				cp ./mlx_dy/libmlx.dylib .
				${GCC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIB} ${OPENGL}


clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}
		${RM} ${LIB}
		# make clean -C ./mlx_st/
		make clean -C ./mlx_dy/
		# ${RM} img.bmp

re:		fclean all
