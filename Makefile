#*******************************  VARIABLES  **********************************#

NAME			=	minishell

# --------------- FILES --------------- #

#-------------  VPATH  ---------------#

vpath %c srcs


LIST_SRCS		=

LIST_HEADERS	=	main.c \
					fizzbuzz.c

# ------------ DIRECTORIES ------------ #

DIR_BUILD		=	.build/
DIR_HEADERS		=	includes/
DIR_LIBFT		=	libft/
libft = $(DIR_LIBFT)libft.a
mlx = $(DIR_MLX)libmlx.a

# ------------- SHORTCUTS ------------- #

OBJS            = $(addprefix $(DIR_BUILD), $(addsuffix .o, $(LIST_SRCS)))
HEADERS		= $(addprefix $(DIR_HEADERS), $(addsuffix .h, $(LIST_HEADERS)))
DEPS            = ${OBJS:.o=.d}
INCLUDES        = -I $(DIR_MLX) -I $(DIR_HEADERS) -I $(DIR_LIBFT)

# ------------ COMPILATION ------------ #

CFLAGS			=	-Wall -Wextra -Werror -g3
DEPS_FLAGS		=	-MMD -MP

# -------------  COMMANDS ------------- #

RM				=	rm -rf
MKDIR			=	mkdir -p

# -------------  MLX ------------- #

OS				= $(shell uname -s)

DIR_MLX		=	mlx_linux/
MLX_FLAGS	=	-lXext -lX11 -lm


#***********************************  RULES  **********************************#

all:			 $(NAME)

# ---------- VARIABLES RULES ---------- #

$(NAME):		 $(OBJS) $(mlx) $(libft)
				$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -L $(DIR_LIBFT) -lft -L $(DIR_MLX) -lmlx $(MLX_FLAGS) -o $(NAME)

# ---------- COMPILED RULES ----------- #

$(DIR_BUILD)%.o: %.c ${HEADERS} | $(DIR_BUILD)
				$(CC) $(CFLAGS) $(DEPS_FLAGS) $(INCLUDES) -O3 -c $< -o $@


$(mlx): FORCE
	            		$(MAKE) -C $(DIR_MLX)

#------------------CREATE REPO OBJS ---------#
$(DIR_BUILD):
		$(MKDIR) $(DIR_BUILD)

$(libft): FORCE
	            $(MAKE) -C $(DIR_LIBFT)
-include $(DEPS)

clean:
				$(MAKE) -C $(DIR_LIBFT) clean
				$(MAKE) -C $(DIR_MLX) clean
				$(RM) $(DIR_BUILD)

fclean: clean
				$(MAKE) -C $(DIR_LIBFT) fclean
				$(RM) $(NAME)

re:				fclean all
				$(MAKE) -C ./

.PHONY: all clean fclean re FORCE mlx libft