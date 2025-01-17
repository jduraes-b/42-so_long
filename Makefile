# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jduraes- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/22 19:08:31 by jduraes-          #+#    #+#              #
#    Updated: 2024/01/24 20:25:34 by jduraes-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
SRC = src/main.c src/mapread.c src/mapread_utils.c src/mlxstart.c src/movement.c src/utils.c
BONUS_SRC = src_bonus/main.c src_bonus/mapread.c src_bonus/mapread_utils.c src_bonus/mlxstart.c src_bonus/movement.c src_bonus/utils.c src_bonus/bonus_funcs.c
OBJS = $(SRC:.c=.o)
BONUS_OBJS = $(BONUS_SRC:.c=.o)
CC = cc -g
CFLAGS = -Wall -Wextra -Werror
IFLAGS = -L ./minilibx-linux -lmlx -Ilmlx -lXext -lX11 -lm
LIBMLX = minilibx-linux/libmlx.a

$(NAME): $(OBJS)
	@make bonus -C libft all
	@make -C minilibx-linux
	$(CC) $(CFLAGS) $(OBJS) $(IFLAGS) -L libft -lft $(LIBMLX) -o $(NAME)

all: $(NAME)

bonus: $(BONUS_OBJS)
	@make bonus -C libft all
	@make -C minilibx-linux
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(IFLAGS) -L libft -lft $(LIBMLX) -o $(NAME)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)
	@make clean -C libft

fclean:	clean
	$(RM) $(NAME) $(BONUS_OBJS)
	@make fclean -C libft

re:	fclean all
	@make re -C libft

.phony: all clean fclean re
