P_SRC_CLI = ./src_cli/
P_OBJ = ./obj/
P_INCLUDE = ../include/
P_LIBFT = ../include/libft/

FILES = $(P_SRC_CLI)main.c \
		$(P_SRC_CLI)table.c \
		$(P_SRC_CLI)get_next_line.c \
		$(P_SRC_CLI)get_next_line_utils.c \

SRC = $(patsubst $(P_SRC_CLI)%.c, $(P_OBJ)%.o, $(FILES))

LIBFT = $(P_LIBFT)libft.a
NAME = CLI

CC = gcc
RM = rm -rf
RMR = rm -rf
CFLAGS = #- -Wall -Werror -Wextra -I ./include/ -g #-fsanitize=address

all: $(NAME)

$(NAME): $(SRC)
	@make --no-print-directory -C $(P_LIBFT)
	@echo Folder for obj Created.
	$(CC) -D BUFFER_SIZE=500 $(SRC) $(LIBFT) -o $(NAME)
	@echo "file(CLI) created."

$(P_OBJ)%.o: %.c
	@mkdir -p $(P_OBJ)
	@$(CC) -c $< -o $@

#VALGRIND--|
val:
	valgrind --leak-check=full --show-leak-kinds=all -s --track-origins=yes ./$(NAME) $(ARG)

clean:
	@$(RM) $(P_OBJ)
	@make clean --no-print-directory -C $(P_LIBFT)
	@rm -f valgrind-out.txt
	@echo All clean.

fclean: clean
	@$(RM) $(NAME)
	@make fclean --no-print-directory -C $(P_LIBFT)

re: fclean all