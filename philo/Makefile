NAME				:=	philo

CC					:=	gcc

CFLAGS				:=	-Wall -Werror -Wextra -g
# CFLAGS				+=	-fsanitize=address

# CFLAGS				+=	-fsanitize=thread
# CFLAGS				+=	-pthread

# LDFLAGS				:=	-fsanitize=address

# LDFLAGS				+=	-fsanitize=thread
# LDFLAGS				+=	-lpthread

SRCS				:=	./main.c \
						./src/init_data.c \
						./src/routine_funcs.c \
						./src/routines.c \
						./src/set_get_funcs.c \
						./src/time.c \
						./src/utils0.c \
						./src/utils1.c

HEADERS				:=	-I ../../LeakSanitizer
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

helgrind:
	@valgrind	--tool=helgrind -s ./philo 201 100 20 10

drd:
	@valgrind	--tool=drd -s ./philo 201 100 20 10

.PHONY: all clean fclean re helgrind drd
