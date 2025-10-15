# Makefile for cub3D parser

NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I include -I libft
LDFLAGS = -L$(LIBFT_DIR) -lft -lm

# Source files
SRC_DIR = src
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/parse_textures.c \
       $(SRC_DIR)/parse_colors.c \
       $(SRC_DIR)/texture_parsing_helpers.c \
       $(SRC_DIR)/map_parsing.c \
       $(SRC_DIR)/env_char_checking.c \
       $(SRC_DIR)/map_checking.c \
       $(SRC_DIR)/error_handlers.c

# Object files
OBJ_DIR = obj
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Rules
all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "Building libft..."
	@make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "✅ $(NAME) compiled successfully!"

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "🧹 Object files cleaned"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "🧹 Executable cleaned"

re: fclean all

test: $(NAME)
	@echo "\n=== Testing complete.cub ==="
	./$(NAME) ../test_maps/complete.cub

.PHONY: all clean fclean re test
