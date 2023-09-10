NAME				:=	philo

CC					:=	gcc

CFLAGS				:=	-Wall -Werror -Wextra
CFLAGS				+=	-g
# CFLAGS				+=	-fsanitize=address

LDFLAGS				:=	-g
# LDFLAGS				+=	-fsanitize=address

SRCS				:=	./main.c \
						./src/parser.c \
						./src/routine_funcs0.c \
						./src/routine_funcs1.c \
						./src/routines.c \
						./src/time.c \
						./src/utils.c \

# HEADERS				:=	-I ../../LeakSanitizer
HEADERS				+=	-I ./include

# LDFLAGS				+=	-L ../../LeakSanitizer -llsan -lc++ -Wno-gnu-include-next

OBJS				:=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) && echo "Compilation of $(NAME) is successful"

%.o: %.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

re: fclean all

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJS)

check:
	@valgrind	./philo 5 500 200 150

.PHONY: all clean fclean re check