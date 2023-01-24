# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: romvan-d <romvan-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 14:23:30 by yhuberla          #+#    #+#              #
#    Updated: 2023/01/24 18:55:50 by romvan-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
OBJS_DIR = Objs
OBJS_DIR_Sources = Objs/Sources

FILES = greet main utils

FILES_BUILTINS = cd cd_utils echo env env_utils exit export pwd unset

FILES += $(addprefix Builtins/, $(FILES_BUILTINS))

FILES_EXEC = exec_cmd forkpipe here_doc pids

FILES += $(addprefix Exec/, $(FILES_EXEC))

FILES_SIGNAL = signal

FILES += $(addprefix Signal/, $(FILES_SIGNAL))

FILES_LEXER = lexer lexer_utils prelexer prelexer_utils

FILES += $(addprefix Lexer/, $(FILES_LEXER))

FILES_REDIRECTIONS = redirs redirs_utils redirs_open

FILES += $(addprefix Redirections/, $(FILES_REDIRECTIONS))

Sources = $(addprefix Sources/, $(addsuffix .c, $(FILES)))

OBJS = $(addprefix $(OBJS_DIR)/, $(Sources:.c=.o))

# ===---===---===---===---===---===---===---===---===---===---===---===---

CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
READLINE = -lreadline -L /Users/$(USER)/.brew/Opt/readline/lib -I /Users/$(USER)/.brew/Opt/readline/include

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
	@mkdir -p $(OBJS_DIR)/Sources/Builtins
	@mkdir -p $(OBJS_DIR)/Sources/Exec
	@mkdir -p $(OBJS_DIR)/Sources/Signal
	@mkdir -p $(OBJS_DIR)/Sources/Lexer
	@mkdir -p $(OBJS_DIR)/Sources/Redirections

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(READLINE) $(LIBFT) -I Includes

$(OBJS_DIR)/Sources/Builtins/%.o: Sources/Builtins/%.c
	$(CC) $(CFLAGS) -I /Users/$(USER)/.brew/Opt/readline/include -c $< -o $(<:.c=.o)
	@mv $(<:.c=.o) $(OBJS_DIR)/Sources/Builtins

$(OBJS_DIR)/Sources/Exec/%.o: Sources/Exec/%.c
	$(CC) $(CFLAGS) -I /Users/$(USER)/.brew/Opt/readline/include -c $< -o $(<:.c=.o)
	@mv $(<:.c=.o) $(OBJS_DIR)/Sources/Exec

$(OBJS_DIR)/Sources/Signal/%.o: Sources/Signal/%.c
	$(CC) $(CFLAGS) -I /Users/$(USER)/.brew/Opt/readline/include -c $< -o $(<:.c=.o)
	@mv $(<:.c=.o) $(OBJS_DIR)/Sources/Signal

$(OBJS_DIR)/Sources/Lexer/%.o: Sources/Lexer/%.c
	$(CC) $(CFLAGS) -I /Users/$(USER)/.brew/Opt/readline/include -c $< -o $(<:.c=.o)
	@mv $(<:.c=.o) $(OBJS_DIR)/Sources/Lexer

$(OBJS_DIR)/Sources/Redirections/%.o: Sources/Redirections/%.c
	$(CC) $(CFLAGS) -I /Users/$(USER)/.brew/Opt/readline/include -c $< -o $(<:.c=.o)
	@mv $(<:.c=.o) $(OBJS_DIR)/Sources/Redirections

$(OBJS_DIR)/Sources/%.o: Sources/%.c
	$(CC) $(CFLAGS) -I /Users/$(USER)/.brew/Opt/readline/include -c $< -o $(<:.c=.o)
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
