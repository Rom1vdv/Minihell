# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: romvan-d <romvan-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/28 12:41:01 by yhuberla          #+#    #+#              #
#    Updated: 2023/01/24 17:15:27 by romvan-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FILES = ft_arraylen ft_atoi ft_atoi_64bits ft_bzero ft_free_arr ft_itoa \
		ft_malloc ft_perror ft_putendl ft_split ft_split_first \
		ft_split_quotes ft_split_quotes_set ft_strchr ft_strchr_quotes \
		ft_strcat ft_strcpy ft_strdup ft_strjoin ft_strjoins ft_strlen \
		ft_strncmp

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
