NAME				:=	philo

CC					:=	gcc

CFLAGS				:=	-Wall -Werror -Wextra -g
# CFLAGS				+=	-g -fsanitize=thread
# CFLAGS				+=	-pthread
# CFLAGS				+=	-fsanitize=address
# to check for data races
# CFLAGS				+=	-fsanitize=thread

# LDFLAGS				:=	-g -fsanitize=thread
LDFLAGS				+=	-lpthread -g
# LDFLAGS				+=	-v
# LDFLAGS				+=	-fsanitize=address

SRCS				:=	./main.c \
						./src/init_data.c \
						./src/routine_funcs.c \
						./src/routines.c \
						./src/set_get_funcs.c \
						./src/time.c \
						./src/utils0.c \
						./src/utils1.c

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
