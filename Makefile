#---------------------------------------------------#
CC 			= cc

CFLAGS 		= -fsanitize=address #-Wall -Wextra -Werror

MLXFLAGS	= -lm #-ldl -lglfw -pthread 

NAME 		= cub3d
#---------------------------------------------------#
OBJ_DIR 	= obj/

SRCS		= \
exec/exec.c\
parsing/parsing_utils.c\
parsing/read_map.c\
exit/exit_parsing.c\
error/error_parsing.c

OBJ_DIR 	= .obj

OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

INCLUDES 	= includes/

HEADERS		= includes/parsing.h includes/exec.h
#---------------------------------------------------#
MLX_DIR		= libs/mlx/

MLX_NAME	= libmlx_Linux.a

MLX_EXEC	= $(addprefix $(MLX_DIR), $(MLX_NAME))
#---------------------------------------------------#
LIBFT_DIR	= libs/libft/

LIBFT_NAME	= libft.a

LIBFT_EXEC	= $(addprefix $(LIBFT_DIR), $(LIBFT_NAME))
#---------------------------------------------------#
all: lib
	$(MAKE) $(NAME)

$(NAME): $(OBJS) $(INCLUDES) $(LIBFT_EXEC)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -I $(INCLUDES) $(MLXFLAGS) $(LIBFT_EXEC) $(MLX_EXEC)

$(OBJ_DIR)/%.o : %.c Makefile $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

lib:
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(MLX_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(NAME)

re:	fclean
	$(MAKE) -C $(LIBFT_DIR) re
	$(MAKE) -C $(MLX_DIR) re
	$(MAKE) all

.PHONY: all lib fclean fclean re
#---------------------------------------------------#