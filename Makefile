# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/24 10:05:34 by karpatel          #+#    #+#              #
#    Updated: 2024/08/09 16:51:36 by karpatel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -Lminilibx-linux -lmlx_Linux -lX11 -lXext
SOURCES = main.c render.c complex_numbers.c events.c optimize.c
OBJECTS = $(SOURCES:.c=.o)
LIBDIR = ./libft
MINILIBX = ./minilibx-linux

all: $(NAME)

$(MINILIBX)/Makefile:
	cd $(MINILIBX) && ./configure

$(NAME): $(OBJECTS) $(MINILIBX)/Makefile
	$(MAKE) -C $(LIBDIR)
	$(MAKE) -C $(MINILIBX)
	$(CC) -o $@ $(OBJECTS) $(CFLAGS) $(LFLAGS) ./libft/libft.a

$(SOURCE_DIR)/%.o: %.c
	$(CC) -I -c $(CFLAGS) $< -o $@

clean:
	$(MAKE) -C $(LIBDIR) $@
	cd $(MINILIBX) && ./configure
	$(MAKE) clean -C $(MINILIBX)
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)
	$(MAKE) clean -C $(MINILIBX)
	$(MAKE) fclean -C $(LIBDIR)

re: fclean all

debug: re

.PHONY: debug all clean fclean re
