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

NAME		= a.out

GCC			= gcc

#OPTFLAGS	= -O2

CFLAGS		= -g -Wall -Wextra -Werror
#CFLAGS		= -g

#MLX		= -Imlx

OPENGL		= -L. libmlx.a -framework OpenGL -framework AppKit

RM			= rm -f

#ARRC		= ar rc

FT_H		= mlx_test.h

#LIB			= libminirt.a

all:	${NAME}

#bonus:	all

#сопоставление *.c и *.o файлов
.c.o:
		${GCC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:${OBJS}
		${GCC} ${CFLAGS} -o ${NAME} ${OBJS} ${OPENGL}
#		${ARRC} ${LIB} ${OBJS}
#		${ARRC} ${LIB} ${FT_H}

#main:
#		${GCC} ${CFLAGS} ${LIB} ft_mnrt_main.c

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}
		${RM} ${LIB}

re:		fclean all
