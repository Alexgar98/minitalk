# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alexigar <alexigar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/23 10:50:50 by alexigar          #+#    #+#              #
#    Updated: 2024/05/29 11:58:27 by alexigar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAMECLI = client
NAMESRV = server

CC = clang
CCFLAGS = -Wall -Werror -Wextra -ggdb

SOURCESCLI = client.c

SOURCESSRV = server.c

OBJSCLI = $(SOURCESCLI:.c=.o)
OBJSSRV = $(SOURCESSRV:.c=.o)

all : $(NAMECLI) $(NAMESRV)

$(NAMECLI) : $(OBJSCLI)
	@$(CC) $(OBJSCLI) -g utils/libft/libft.a utils/ft_printf/libftprintf.a -o $(NAMECLI)
$(NAMESRV) : $(OBJSSRV)
	@$(CC) $(OBJSSRV) -g utils/libft/libft.a utils/ft_printf/libftprintf.a -o $(NAMESRV)

%.o : %.c
	@$(CC) -c $(CCFLAGS) $< -o $@

clean :
	@rm -rf $(OBJSCLI) $(OBJSSRV)

fclean : clean
	@rm -rf $(NAMECLI) $(NAMESRV)

re : fclean all
.PHONY : all clean fclean re
