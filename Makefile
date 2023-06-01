#---------------------------------------------------#
CC 			= cc

CFLAGS 		=# -Wall -Wextra -Werror

MLXFLAGS	= -L/libs/mlx -Imlx_linux -lXext -lX11 -lm

NAME 		= cub3D
#---------------------------------------------------#
OBJ_DIR 	= obj/

SRCS		= \
src/exec/actions.c\
src/exec/collision.c\
src/exec/exec.c\
src/exec/events.c\
src/exec/img_utils.c\
src/exec/inits.c\
src/exec/ray_depth.c\
src/exec/rays.c\
src/exec/texture.c\
src/exec/utils.c\
src/exit/exit_exec.c\
src/exit/exit_parsing.c\
src/parsing/parsing_map.c\
src/parsing/parsing_utils.c\
src/parsing/read_map.c\
main.c

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

.PHONY: all lib fclean re
#---------------------------------------------------#