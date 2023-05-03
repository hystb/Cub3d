#---------------------------------------------------#
CC 			= cc

CFLAGS 		= -Wall -Wextra -Werror #-fsanitize=address -g3

MLXFLAGS	= -L/libs/mlx -Imlx_linux -lXext -lX11 -lm -lz #-ldl -lglfw -pthread -lm 

NAME 		= cub3D
#---------------------------------------------------#
OBJ_DIR 	= obj/

SRCS		= \
main.c\
parsing/parsing_utils.c\
parsing/read_map.c\
parsing/parsing_map.c\
exit/exit_parsing.c\
error/error_parsing.c\

OBJ_DIR 	= .obj

OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

INCLUDES 	= includes/

HEADERS		= includes/parsing.h
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
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -I $(INCLUDES) $(LIBFT_EXEC) $(MLX_EXEC) $(MLXFLAGS) 

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