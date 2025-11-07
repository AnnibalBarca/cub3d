NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -I includes -I libft -I minilibx-linux -g3
OBJ_DIR = src/obj
SRC_DIR = src

SRC_ALL =	$(SRC_DIR)/main.c	\
            $(SRC_DIR)/exec/draw.c	\
            $(SRC_DIR)/exec/handle_player.c	\
            $(SRC_DIR)/exec/time.c	\
            $(SRC_DIR)/exec/exec.c	\
            $(SRC_DIR)/exec/minimap.c	\
            $(SRC_DIR)/exec/raycast.c	\
            $(SRC_DIR)/exec/dda.c	\
            $(SRC_DIR)/exec/texture.c	\
            $(SRC_DIR)/utils/init.c \
            $(SRC_DIR)/utils/error.c \
			$(SRC_DIR)/utils/input.c \
            $(SRC_DIR)/utils/cleanup.c \
            $(SRC_DIR)/utils/minimap_utils.c \
            $(SRC_DIR)/parsing/parse_textures.c \
            $(SRC_DIR)/parsing/parse_colors.c \
            $(SRC_DIR)/parsing/parsing_helpers.c \
            $(SRC_DIR)/parsing/map_parsing.c \
            $(SRC_DIR)/parsing/env_char_checking.c \
            $(SRC_DIR)/parsing/map_checking.c


OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_ALL:.c=.o))
DEPS = $(OBJ:.o=.d)
NB = $(words $(SRC_ALL))

LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx_Linux.a

RST = \033[0m
GREEN = \033[38;5;46m
CYAN = \033[38;5;51m
PURPLE = \033[38;5;129m
PINK = \033[38;5;199m
BLUE = \033[38;2;64;224;208m
RED = \033[0;91m

all: $(LIBFT) $(MLX) $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	@printf "\r\033[K$(GREEN)✓ Linking $(CYAN)$(NAME)$(RST)\r"
	@printf "$(GREEN)✓ cub3d created!$(NC)$(RST)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)
	@printf "$(BLUE)╔════════════════════════════════════════╗$(RST)\n"
	@printf "$(BLUE)║$(RST)        $(GREEN)✓ COMPILATION SUCCESS! ✓$(RST)        $(BLUE)║$(RST)\n"
	@printf "$(BLUE)╚════════════════════════════════════════╝$(RST)\n"

$(OBJ_DIR)/%.o: %.c Makefile
	@mkdir -p $(dir $@)
	@printf "\r\033[K$(CYAN)⚙$(RST)  Compiling $(PURPLE)%-50s$(RST)\r" "$<"
	@$(CC) $(CFLAGS) -o $@ -c $<

-include $(DEPS)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@printf "$(PINK)✓ MLX Compiling...$(RST)\r"
	@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1

clean:
	@echo "$(RED)🗑  Cleaning objects...$(RST)"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	@echo "$(RED)🗑  Removing $(NAME)...$(RST)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
