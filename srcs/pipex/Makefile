# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbernard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/14 16:22:44 by mbernard          #+#    #+#              #
#    Updated: 2024/03/26 09:21:03 by mbernard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = pipex
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g
MKDIR = mkdir -p
RMDIR = rm -rf
#colors
_GREEN=\033[0;32m
_BLUE=\033[0;34m
_YELLOW=\033[0;33m
_END=\033[0m
# ---------------------------------- Sources --------------------------------- #

SRCS_PIPEX =	pipex_bonus	errors_bonus	join_bonus	paths_bonus	cmds_bonus	\
				pipe_utils_bonus	utils_bonus	child_care_bonus	heredoc_bonus
SRCS_PIPEX_WITH_DIR = $(addprefix ${SRCS_PIPEX_DIR}, ${SRCS_PIPEX})

# ---------------------------------- Repertories ----------------------------- #
HEADER_DIR = header/
OBJS_DIR = .objs/
SRCS_PIPEX_DIR = src/
HEADER = $(addprefix ${HEADER_DIR}, pipex_bonus.h)
OBJS = $(addprefix ${OBJS_DIR}, $(addsuffix .o, ${SRCS_PIPEX}))
DEPS = ${OBJS:.o=.d}

# ---------------------------------- Lib Gestion ----------------------------- #
LIBFT_DIR = ../libft/
LIBFT = $(addprefix ${LIBFT_DIR}, libft.a)
INCLUDES = -I ${LIBFT_DIR} -I ${HEADER_DIR} 
# ---------------------------------- Compilation ----------------------------- #
all: ${NAME} ${OBJS} Makefile | ${OBJS_DIR}
 
${NAME}: ${OBJS} ${LIBFT} Makefile
	@echo "${_BLUE}Compiling pipex...${_END}"
	@${CC} ${CFLAGS} ${OBJS}  ${INCLUDES} ${LIBFT} -o $@
	@echo "${_BLUE}Pipex done !${_END}"

${OBJS_DIR}%.o: ${SRCS_PIPEX_DIR}%.c ${HEADER} Makefile | ${OBJS_DIR}
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

${LIBFT}: FORCE
	@echo "${_GREEN}Building Libft${_END}"
	@$(MAKE) -s -C ${LIBFT_DIR}
	@echo "${_GREEN}Libft done${_END}"

-include ${DEPS}
# ---------------------------------- Create Repertory ---------------------- #
${OBJS_DIR}:
			${MKDIR} ${OBJS_DIR}

## ---------------------------------- Clean ----------------------------------- #
clean:
	${RMDIR} ${OBJS_DIR}

fclean: clean
	${RM} ${NAME}

clean_lib: clean
	@echo "${_BLUE}Cleaning Libft"
	@${MAKE} -s clean -C $(LIBFT_DIR)
	@echo "Libft cleaned${_END}"

fclean_lib: fclean clean_lib
	${RM} ${LIBFT}

re:    fclean_lib
	${MAKE} ${NAME}

re_pipex_only: fclean
	${MAKE} ${NAME}

FORCE:

# ---------------------------------- Phony ----------------------------------- #
.PHONY: all clean clean_lib fclean fclean_lib re re_pipex_only FORCE
