
NAME			=	minishell

#-------------  VPATH  ---------------#

vpath %c srcs

# --------------- FILES --------------- #

LIST_SRCS		=  main lexer/lexer lexer/token

LIST_HEADERS	= error general lexer

# ------------ DIRECTORIES ------------ #

DIR_BUILD		=	.build/
DIR_HEADERS		=	includes/
DIR_LIBFT		=	libft/
libft			=	$(DIR_LIBFT)libft.a

# ------------- SHORTCUTS ------------- #

OBJS            = $(addprefix $(DIR_BUILD), $(addsuffix .o, $(LIST_SRCS)))
HEADERS			= $(addprefix $(DIR_HEADERS), $(addsuffix .h, $(LIST_HEADERS)))
DEPS            = ${OBJS:.o=.d}
INCLUDES        = -I $(DIR_HEADERS) -I $(DIR_LIBFT)

# ------------ COMPILATION ------------ #

CFLAGS			=	-Wall -Wextra -Werror -g3
DEPS_FLAGS		=	-MMD -MP

# -------------  COMMANDS ------------- #

RM				=	rm -rf
MKDIR			=	mkdir -p

#***********************************  RULES  **********************************#

all:			 $(NAME)

# ---------- VARIABLES RULES ---------- #

$(NAME):		 $(OBJS) $(libft)
				$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -L $(DIR_LIBFT) -lft -o $(NAME)

# ---------- COMPILED RULES ----------- #

$(DIR_BUILD)%.o: %.c $(DIR_BUILD)
				$(CC) $(CFLAGS) $(DEPS_FLAGS) $(INCLUDES) -O3 -c $< -o $@

#---------- CREATE REPO OBJS ---------#

$(DIR_BUILD):
		@echo "Création du répertoire $(DIR_BUILD)"
		$(MKDIR) $(DIR_BUILD)


$(libft): FORCE
	            $(MAKE) -C $(DIR_LIBFT)
-include $(DEPS)

clean:
				$(MAKE) -C $(DIR_LIBFT) clean
				$(RM) $(DIR_BUILD)

fclean: clean
				$(MAKE) -C $(DIR_LIBFT) fclean
				$(RM) $(NAME)

re:				fclean all
				$(MAKE) -C ./

.PHONY: all clean fclean re FORCE libft
