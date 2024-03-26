cmake_minimum_required(VERSION 3.27)
project(minishell C)

set(CMAKE_C_STANDARD 11)

include_directories(includes)
include_directories(libft/inc)
find_library(READLINE_LIBRARY readline)

add_executable(minishell
        libft/inc/get_next_line.h
        libft/inc/libft.h
        libft/src/ft_is/ft_isalnum.c
        libft/src/ft_is/ft_isalpha.c
        libft/src/ft_is/ft_isascii.c
        libft/src/ft_is/ft_isdigit.c
        libft/src/ft_is/ft_isprint.c
        libft/src/ft_lst/ft_lstadd_back.c
        libft/src/ft_lst/ft_lstadd_front.c
        libft/src/ft_lst/ft_lstclear.c
        libft/src/ft_lst/ft_lstdelone.c
        libft/src/ft_lst/ft_lstiter.c
        libft/src/ft_lst/ft_lstlast.c
        libft/src/ft_lst/ft_lstmap.c
        libft/src/ft_lst/ft_lstnew.c
        libft/src/ft_lst/ft_lstsize.c
        libft/src/ft_mem/ft_bzero.c
        libft/src/ft_mem/ft_calloc.c
        libft/src/ft_mem/ft_memchr.c
        libft/src/ft_mem/ft_memcmp.c
        libft/src/ft_mem/ft_memcpy.c
        libft/src/ft_mem/ft_memmove.c
        libft/src/ft_mem/ft_memset.c
        libft/src/ft_mem/ft_realloc.c
        libft/src/ft_printf/ft_printf.c
        libft/src/ft_printf/numbers_functions.c
        libft/src/ft_printf/strings_functions.c
        libft/src/ft_put/ft_putchar_fd.c
        libft/src/ft_put/ft_putendl_fd.c
        libft/src/ft_put/ft_putnbr_fd.c
        libft/src/ft_put/ft_putstr_fd.c
        libft/src/ft_str/ft_split.c
        libft/src/ft_str/ft_strchr.c
        libft/src/ft_str/ft_strcmp.c
        libft/src/ft_str/ft_strdup.c
        libft/src/ft_str/ft_striteri.c
        libft/src/ft_str/ft_strjoin.c
        libft/src/ft_str/ft_strlcat.c
        libft/src/ft_str/ft_strlcpy.c
        libft/src/ft_str/ft_strlen.c
        libft/src/ft_str/ft_strmapi.c
        libft/src/ft_str/ft_strncmp.c
        libft/src/ft_str/ft_strnstr.c
        libft/src/ft_str/ft_strrchr.c
        libft/src/ft_str/ft_strtrim.c
        libft/src/ft_str/ft_substr.c
        libft/src/ft_to/ft_atoi.c
        libft/src/ft_to/ft_atol.c
        libft/src/ft_to/ft_itoa.c
        libft/src/ft_to/ft_tolower.c
        libft/src/ft_to/ft_toupper.c
        libft/src/gnl/get_next_line.c
        libft/src/gnl/get_next_line_utils.c
        libft/src/utils.c
        libft/src/hashmap_dictionnary/hm_clear.c
        libft/src/hashmap_dictionnary/hm_add_elem.c
        libft/src/hashmap_dictionnary/hm_get_content.c
        libft/src/hashmap_dictionnary/hm_delete_elem.c
        libft/src/hashmap_dictionnary/hm_get_elem.c
        libft/src/hashmap_dictionnary/hm_get_index.c
        libft/src/hashmap_dictionnary/hm_init.c
        libft/src/hashmap_dictionnary/hm_size.c
        libft/src/hashmap_dictionnary/hm_print.c

        includes/utils.h
        includes/parser.h
        includes/minishell.h
        includes/error.h
        includes/lexer.h
        includes/signals.h



        srcs/main.c
        srcs/utils/error.c
        srcs/lexer/tokenization.c
        srcs/parser/parser.c
        srcs/lexer/operator.c
        srcs/lexer/builtin.c
        srcs/env_variables/env_variables.c
        srcs/expansion/expansion.c
        srcs/utils/free.c
        srcs/lexer/split_string.c
        srcs/utils/print.c
        srcs/parser/create_tables_from_tokens.c
        srcs/lexer/count_tokens.c
        srcs/env_variables/envp_calcultate_size.c
        srcs/init.c
        srcs/signal.c
)

target_link_libraries(minishell ${READLINE_LIBRARY})
