NAME = magic_filter

CC = gcc

RM = rm -f

CFLAGS = -lm

SRCS = 	main.c\
	parse_bmp.c\
	pixel.c\
	filter.c\
	display.c\
	list.c

OBJS = $(SRCS:.c=.o)



all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CFLAGS)

clean:
	$(RM) $(NAME)

fclean: clean
	$(RM) $(OBJS)

re: fclean all
