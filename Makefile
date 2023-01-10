# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 14:23:30 by yhuberla          #+#    #+#              #
#    Updated: 2023/01/10 19:36:11 by yhuberla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
OBJS_DIR = Objs
OBJS_DIR_Sources = Objs/Sources

FILES = builtins builtins2 cd colors env export lexer main signal test unset \
		utils

Sources = $(addprefix Sources/, $(addsuffix .c, $(FILES)))

OBJS = $(addprefix $(OBJS_DIR)/, $(Sources:.c=.o))

# ===---===---===---===---===---===---===---===---===---===---===---===---

CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
READLINE = -lreadline #-L /Users/$(USER)/.brew/Cellar/readline/lib -I /Users/$(USER)/.brew/Cellar/readline/include

# ===---===---===---===---===---===---===---===---===---===---===---===---

LIBFT_DIR = Libft
LIBFT_PATH = $(LIBFT_DIR)/libft.a
LIBFT_OBJS = $(LIBFT_DIR)/Objs

LIBFT = $(LIBFT_PATH)

# ===---===---===---===---===---===---===---===---===---===---===---===---

all: $(OBJS_DIR_Sources) $(NAME)

$(OBJS_DIR_Sources):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/Sources

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(READLINE) $(LIBFT)

$(OBJS_DIR)/Sources/%.o: Sources/%.c
	$(CC) $(CFLAGS) -I /Users/$(USER)/.brew/Cellar/readline/include -c $< -o $(<:.c=.o)
	@mv $(<:.c=.o) $(OBJS_DIR)/Sources

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make fclean -C $(LIBFT_DIR)
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re NAME OBJS_DIR_Sources LIBFT