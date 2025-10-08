NAME = libft.a
CFLAGS = -Wall -Wextra -Werror -g
CC = cc
BUILD_DIR = build
HEADER_DIR = libft.h
SRC_LIBFT = ft_isalpha.c ft_bzero.c ft_isascii.c ft_isprint.c ft_strlcpy.c \
    ft_strncmp.c ft_toupper.c ft_memcpy.c ft_memset.c ft_isalnum.c \
    ft_isdigit.c ft_strlcat.c ft_strlen.c ft_tolower.c ft_split.c \
    ft_strchr.c ft_strrchr.c ft_memchr.c ft_strnstr.c ft_calloc.c \
    ft_strdup.c ft_strjoin.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c \
    ft_putstr_fd.c ft_putendl_fd.c ft_strlen.c ft_memmove.c ft_memcmp.c \
    ft_substr.c ft_striteri.c ft_putnbr_fd.c ft_atoi.c ft_strtrim.c \
    ft_printf.c ft_putchar_len.c ft_putnbr_base.c ft_putnbr_ptr.c get_next_line.c get_next_line_utils.c \


SRC_BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
    ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
    ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

SRC_ALL = $(SRC_LIBFT) $(SRC_BONUS)

OBJECTS = $(SRC_LIBFT:%.c=$(BUILD_DIR)/%.o)
OBJECTS_BONUS = $(SRC_BONUS:%.c=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR) $(NAME)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c $(HEADER_DIR) Makefile
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

bonus: $(OBJECTS) $(OBJECTS_BONUS)
	@make SRC_LIBFT="$(SRC_ALL)"

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus