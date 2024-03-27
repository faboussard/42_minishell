
NAME			=	minishell

#-------------  VPATH  ---------------#

vpath %c srcs lexer env_variables parser expansion utils pipex

# --------------- FILES --------------- #

LIST_SRCS		=  main signal init\
				lexer/tokenization lexer/operator lexer/builtin lexer/count_tokens lexer/split_string\
				env_variables/env_variables env_variables/envp_calcultate_size\
				parser/parser parser/create_tables_from_tokens\
				expansion/expansion \
				utils/free utils/print utils/error \
				pipex/pipex_bonus	pipex/errors_bonus	pipex/join_bonus	pipex/paths_bonus	pipex/cmds_bonus\
                pipex/pipe_utils_bonus	pipex/utils_bonus	pipex/child_care_bonus	pipex/heredoc_bonus

LIST_HEADERS	= error utils lexer minishell parser signals pipex_bonus

# ------------ DIRECTORIES ------------ #

DIR_BUILD		=	.build/
DIR_HEADERS		=	includes/
DIR_LIBFT		=	libft/
HEADER_LIBFT    =   libft/inc/
libft			=	$(DIR_LIBFT)libft.a

# ------------- SHORTCUTS ------------- #

OBJS            = $(addprefix $(DIR_BUILD), $(addsuffix .o, $(LIST_SRCS)))
HEADERS			= $(addprefix $(DIR_HEADERS), $(addsuffix .h, $(LIST_HEADERS)))
DEPS            = ${OBJS:.o=.d}
INCLUDES        = -I $(DIR_HEADERS) -I $(DIR_LIBFT) -I $(HEADER_LIBFT)

# ------------ COMPILATION ------------ #

CC				=	clang
CFLAGS			=	-Wall -Wextra -Werror
DEPS_FLAGS		=	-MMD -MP

# -------------  COMMANDS ------------- #

RM				=	rm -rf
MKDIR			=	mkdir -p

#***********************************  RULES  **********************************#

all:			 $(NAME)

# ---------- VARIABLES RULES ---------- #

$(NAME):		 $(OBJS) $(libft)
				$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -L $(DIR_LIBFT) -lft -lreadline -o $(NAME)

# ---------- COMPILED RULES ----------- #

$(DIR_BUILD)%.o: %.c $(DIR_BUILD)
				$(CC) $(CFLAGS) $(INCLUDES) -O3 -c $< -o $@

#---------- CREATE REPO OBJS ---------#

$(DIR_BUILD):
		@echo "Création du répertoire $(DIR_BUILD)"
		$(MKDIR) -p $(DIR_BUILD)
		@mkdir -p $(DIR_BUILD)/lexer
		@mkdir -p $(DIR_BUILD)/env_variables
		@mkdir -p $(DIR_BUILD)/parser
		@mkdir -p $(DIR_BUILD)/expansion
		@mkdir -p $(DIR_BUILD)/utils
		@mkdir -p $(DIR_BUILD)/pipex

$(libft): FORCE
	            $(MAKE) -C $(DIR_LIBFT)

valgrind:       $(NAME)
		valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --suppressions=./ignore_leaks.supp ./$(NAME)

debug: CFLAGS := $(filter-out -Werror,$(CFLAGS))
debug: all

clean:
				$(MAKE) -C $(DIR_LIBFT) clean
				$(RM) $(DIR_BUILD)

fclean: clean
				$(MAKE) -C $(DIR_LIBFT) fclean
				$(RM) $(NAME)

re:				fclean all
				$(MAKE) -C ./

.PHONY: all clean fclean re FORCE libft
