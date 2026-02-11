# Makefile for SO_LONG

# Standard
NAME				= so_long

# Directories
MINILIBX			= ./minilibx-linux/libmlx.a
LIBFT				= ./Lib/libft.a
HDR					= hdr/
SRC_DIR				= src/
OBJ_DIR				= obj/

# Compiler and CFlags
CC					= cc
CFLAGS				= -Wall -Werror -Wextra -I$(HDR) -Iinclude
RM					= rm -f
MLX_FLAGS			= -lXext -lX11 -lm -lz

# Source Files
#UTILITIES_DIR		=	$(SRC_DIR)Commands/push.c \
						$(SRC_DIR)Commands/reverse.c \
						$(SRC_DIR)Commands/rotate.c \
						$(SRC_DIR)Commands/swap.c \

SO_LONG_DIR			=	$(SRC_DIR)So_long/so_long.c \
						

#ALGORITHM_DIR		=	$(SRC_DIR)Algorithm/sort_stacks.c \
						$(SRC_DIR)Algorithm/sort_three.c \
						$(SRC_DIR)Algorithm/stack_init_a_to_b.c \
						$(SRC_DIR)Algorithm/stack_init_b_to_a.c \





# Concatenate all source files
SRCS 				= $(SO_LONG_DIR)

# Apply the pattern substitution to each source file in SRC and produce a corresponding list of object files in the OBJ_DIR
OBJ 				= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# Build rules

all: 				$(NAME)

$(LIBFT):
					@make -C ./Lib

$(MINILIBX):		
					@make -C minilibx-linux


$(NAME): 			$(OBJ) $(LIBFT) $(MINILIBX)
					@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MINILIBX) $(MLX_FLAGS) -o $(NAME)

# Compile object files from source files
$(OBJ_DIR)%.o:		$(SRC_DIR)%.c 
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) -c $< -o $@

clean:
					@$(RM) -r $(OBJ_DIR)
					@make clean -C ./Lib

fclean: 			clean
					@$(RM) $(NAME)
					@$(RM) $(LIBFT)
					@$(RM) $(MINILIBX)

re: 				fclean all

# Phony targets represent actions not files
.PHONY: 			start all clean fclean re