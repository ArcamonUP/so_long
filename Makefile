# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/09 12:12:24 by kbaridon          #+#    #+#              #
#    Updated: 2024/12/17 16:23:13 by kbaridon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = so_long
SRCDIR = src
LIBDIR = lib/minilibx-linux
LIBFT = libft
INCLUDES = -I$(LIBDIR)
LDFLAGS = -L$(LIBDIR) -lmlx -lXext -lX11 -lm -lz
HEADERS = $(LIBFT)/libft.h $(SRCDIR)/so_long.h

SRC =	so_long.c \
		parse.c \
		check_exit_possible.c \
		check_collectibles.c \
		display_map.c \
		event_listener.c \
		utils.c

OBJS = $(addprefix $(SRCDIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT)/libft.a $(LDFLAGS) $(INCLUDES) -o $(NAME)

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -I $(LIBFT) -c $< -o $@

$(OBJS): $(HEADERS)

clean:
	$(MAKE) clean -C $(LIBFT)
	rm -rf $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
