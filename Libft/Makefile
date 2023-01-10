# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/28 12:41:01 by yhuberla          #+#    #+#              #
#    Updated: 2023/01/10 11:09:56 by yhuberla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FILES = ft_arraylen ft_bzero ft_free_arr ft_putendl ft_split ft_strchr \
		ft_strjoin ft_strlen ft_strncmp

SRCS = $(addsuffix .c, $(FILES))

OBJS = $(addprefix ../Objs/Libft/, $(SRCS:.c=.o))

DIR_OBJ = ../Objs/Libft

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

CC = gcc

all: $(DIR_OBJ) $(NAME)

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

$(NAME): $(OBJS)
	@ar -rcs $(NAME) $(OBJS)

$(DIR_OBJ)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
	@mv $(<:.c=.o) $(DIR_OBJ)

fclean:
	@$(RM) $(NAME)

re: fclean all

.PHONY: all fclean re
