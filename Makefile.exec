NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -I includes -I libft -I minilibx-linux -g3
OBJ_DIR = src/obj
SRC_DIR = src

SRC_ALL =	$(SRC_DIR)/exec/main.c	\
			$(SRC_DIR)/exec/init.c	\

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_ALL:.c=.o))
DEPS = $(OBJ:.o=.d)
NB = $(words $(SRC_ALL))
COUNTER = 0

LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx_Linux.a

RST = \033[0m
RED = \033[38;5;196m
RED_ORANGE = \033[38;5;202m
ORANGE = \033[38;5;208m
ORANGE_YELLOW = \033[38;5;214m
YELLOW = \033[38;5;220m
YELLOW_GREEN = \033[38;5;154m
LIGHT_GREEN = \033[38;5;118m
GREEN = \033[38;5;46m
CYAN = \033[38;5;51m
PURPLE = \033[38;5;129m
PINK = \033[38;5;199m
BLUE=\033[38;2;64;224;208m

define loading_bar
	$(eval COUNTER=$(shell echo $$(($(COUNTER)+1))))
	@CURRENT=$$(( $(COUNTER) * 50 / $(NB) )); \
	PERCENT=$$(( $(COUNTER) * 100 / $(NB) )); \
	LOADING_BAR="["; \
	for i in $$(seq 1 $$CURRENT); do \
		if [ $$i -le 6 ]; then \
		    LOADING_BAR=$$LOADING_BAR"$(RED)█$(RST)"; \
		elif [ $$i -le 12 ]; then \
		    LOADING_BAR=$$LOADING_BAR"$(RED_ORANGE)█$(RST)"; \
		elif [ $$i -le 18 ]; then \
		    LOADING_BAR=$$LOADING_BAR"$(ORANGE)█$(RST)"; \
		elif [ $$i -le 25 ]; then \
		    LOADING_BAR=$$LOADING_BAR"$(ORANGE_YELLOW)█$(RST)"; \
		elif [ $$i -le 31 ]; then \
		    LOADING_BAR=$$LOADING_BAR"$(YELLOW)█$(RST)"; \
		elif [ $$i -le 37 ]; then \
		    LOADING_BAR=$$LOADING_BAR"$(YELLOW_GREEN)█$(RST)"; \
		elif [ $$i -le 43 ]; then \
		    LOADING_BAR=$$LOADING_BAR"$(LIGHT_GREEN)█$(RST)"; \
		else \
		    LOADING_BAR=$$LOADING_BAR"$(GREEN)█$(RST)"; \
		fi; \
	done; \
	for i in $$(seq $$(($$CURRENT + 1)) 50); do \
	    LOADING_BAR=$$LOADING_BAR"$(RST)░"; \
	done; \
	LOADING_BAR=$$LOADING_BAR"]"; \
	printf "\033[K\r%b %3d%% $(CYAN)⚙$(RST)  Compiling $(PURPLE)%s$(RST) ($(GREEN)%d$(RST)/$(BLUE)%d$(RST))" \
	    "$$LOADING_BAR" "$$PERCENT" "$<" "$(COUNTER)" "$(NB)";
endef

all:	$(LIBFT) $(MLX) $(OBJ_DIR) $(NAME)

$(OBJ_DIR)/%.o: %.c Makefile
	@mkdir -p $(dir $@)
	$(call loading_bar)
	@$(CC) $(CFLAGS) -o $@ -c $<

-include $(DEPS)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@echo ""
	@printf "$(GREEN)✓ Linking $(CYAN)$(NAME)$(RST)...\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)
	@printf "$(BLUE)╔════════════════════════════════════════╗$(RST)\n"
	@printf "$(BLUE)║$(RST)        $(GREEN)✓ COMPILATION SUCCESS! ✓$(RST)        $(BLUE)║$(RST)\n"
	@printf "$(BLUE)╚════════════════════════════════════════╝$(RST)\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

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
