P_API = ./API/
P_OBJ_API = ./obj_API/
P_INCLUDE = ./includes/

FILES = $(P_API)main.c $(P_API)mjson.c $(P_API)mongoose.c \
		$(P_API)get_next_line.c $(P_API)get_next_line_utils.c
		

SRC = $(patsubst $(P_API)%.c, $(P_OBJ_API)%.o, $(FILES))

NAME = API_REST

CC = gcc
RM = rm -rf
RMR = rm -rf
CFLAGS = #- -Wall -Werror -Wextra -I ./include/ -g #-fsanitize=address

all: $(NAME)

$(NAME): $(SRC)
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME) -lcurl
	@echo "file(API_REST) created."

$(P_OBJ_API)%.o: $(P_API)%.c
	@mkdir -p $(P_OBJ_API)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(P_OBJ_API)
	@rm -f valgrind-out.txt
	@echo All clean.

fclean: clean
	@$(RM) $(NAME)

re: fclean all