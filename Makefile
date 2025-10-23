# Makefile for cub3D parser

NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I includes -I libft
LDFLAGS = -L$(LIBFT_DIR) -lft -lm -fPIE

# Source files
SRC_DIR = src
SRCS = $(SRC_DIR)/parsing/main.c \
       $(SRC_DIR)/utils/init.c \
       $(SRC_DIR)/utils/error.c \
       $(SRC_DIR)/parsing/parse_textures.c \
       $(SRC_DIR)/parsing/parse_colors.c \
       $(SRC_DIR)/parsing/texture_parsing_helpers.c \
       $(SRC_DIR)/parsing/map_parsing.c \
       $(SRC_DIR)/parsing/env_char_checking.c \
       $(SRC_DIR)/parsing/map_checking.c \

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
	@mkdir -p $(dir $@)
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
