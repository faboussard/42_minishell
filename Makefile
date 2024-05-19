
NAME			=	minishell

#-------------  VPATH  ---------------#

vpath %c srcs lexer joiner env_variables parser expansion utils exec builtins

# --------------- FILES --------------- #

LIST_SRCS		=  main\
                signals/signal signals/signal_interrupt\
				lexer/tokenization lexer/operator lexer/builtin lexer/count_tokens \
				lexer/token_list lexer/token_utils \
				joiner/join_tokens joiner/join_tokens_utils \
				env_variables/env_variables env_variables/env_utils env_variables/envp_list_utils\
				env_variables/manage_envp_lists env_variables/fake_env env_variables/shell_level\
				parser/parser parser/parser_utils parser/create_process_list parser/process_list parser/check_syntax parser/print_error_syntax\
				parser/token_requalif_utils parser/check_quotes parser/create_tables_in_process_list\
				builtins/unset_builtin builtins/export_builtin builtins/env_builtin builtins/exit_builtin builtins/exit_builtin2\
				builtins/cd_builtin builtins/cd_utils \
				builtins/ft_realpath builtins/realpath_utils builtins/ft_split_list \
				builtins/pwd_builtin \
				builtins/builtins_utils builtins/echo_builtin\
				builtins/export_print builtins/export\
				expansion/expansion expansion/expansion_utils expansion/expansion_utils_2 expansion/add_after_special_char\
				utils/free utils/free_utils utils/print utils/error \
				exec/exec exec/errors exec/errors_exit	exec/paths	exec/fd_management \
                exec/safe_utils	exec/utils	exec/child_care	exec/heredoc #exec/here_cat

LIST_HEADERS	= utils lexer minishell parser signals exec builtins ft_realpath

# ------------ DIRECTORIES ------------ #

DIR_BUILD		=	.build/
SUPP_LEAK_DIR := $(shell pwd)
SUBDIRS := .build/lexer .build/env_variables .build/parser .build/expansion \
			.build/joiner .build/utils .build/exec .build/builtins .build/signals
DIR_HEADERS		=	includes/
DIR_LIBFT		=	libft/
HEADER_LIBFT    =   libft/inc/
libft			=	$(DIR_LIBFT)libft.a

# ------------- SHORTCUTS ------------- #

OBJS            = $(addprefix $(DIR_BUILD), $(addsuffix .o, $(LIST_SRCS)))
HEADERS					= $(addprefix $(DIR_HEADERS), $(addsuffix .h, $(LIST_HEADERS)))
DEPS            = ${OBJS:.o=.d}
INCLUDES        = -I $(DIR_HEADERS) -I $(DIR_LIBFT) -I $(HEADER_LIBFT)

# ------------ COMPILATION ------------ #

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror -g3 # -fsanitize=address #-fPIE

DEPS_FLAGS		=	-MMD -MP

# -------------  COMMANDS ------------- #

RM				=	rm -rf
MKDIR			=	mkdir -p

#***********************************  RULES  **********************************#

all:			 $(NAME)

# ---------- VARIABLES RULES ---------- #

$(NAME): $(OBJS) $(libft) Makefile
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -L $(DIR_LIBFT) -lft -lreadline -o $(NAME)

# ---------- COMPILED RULES ----------- #

$(DIR_BUILD)%.o: %.c Makefile | $(SUBDIRS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

#---------- CREATE REPO OBJS ---------#

$(SUBDIRS): $(DIR_BUILD)
	@echo "Création du sous-répertoire $@"
	@$(MKDIR) $@

$(DIR_BUILD):
	@echo "Création du répertoire $(DIR_BUILD)"
	@$(MKDIR) $(DIR_BUILD)

$(libft): FORCE
	            $(MAKE) -C $(DIR_LIBFT)

valgrind:       $(NAME)
		valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --suppressions=$(SUPP_LEAK_DIR)/ignore_leaks.supp ./$(NAME)

debug: clean
	$(MAKE) CFLAGS="-g"

clean:
				$(MAKE) -C $(DIR_LIBFT) clean
				$(RM) $(DIR_BUILD)

fclean: clean
				$(MAKE) -C $(DIR_LIBFT) fclean
				$(RM) $(NAME)

re:				fclean all
				$(MAKE) -C ./

.PHONY: all clean fclean re FORCE libft

-include $(DEPS)