NAME=libft.a

SRCS=src/ft_is/ft_isalnum.c\
	    src/ft_is/ft_isalpha.c\
	    src/ft_is/ft_isascii.c\
	    src/ft_is/ft_isdigit.c\
	    src/ft_is/ft_isprint.c\
	    src/ft_lst/ft_lstadd_back.c\
	    src/ft_lst/ft_lstadd_front.c\
	    src/ft_lst/ft_lstclear.c\
	    src/ft_lst/ft_lstdelone.c\
	    src/ft_lst/ft_lstiter.c\
	    src/ft_lst/ft_lstlast.c\
	    src/ft_lst/ft_lstmap.c\
	    src/ft_lst/ft_lstnew.c\
	    src/ft_lst/ft_lstsize.c\
	    src/ft_mem/ft_bzero.c\
	    src/ft_mem/ft_calloc.c\
	    src/ft_mem/ft_memchr.c\
	    src/ft_mem/ft_memcmp.c\
	    src/ft_mem/ft_memcpy.c\
	    src/ft_mem/ft_memmove.c\
	    src/ft_mem/ft_memset.c\
	    src/ft_mem/ft_realloc.c\
	    src/ft_printf/ft_printf.c\
	    src/ft_printf/numbers_functions.c\
	    src/ft_printf/strings_functions.c\
	    src/ft_put/ft_putchar_fd.c\
	    src/ft_put/ft_putendl_fd.c\
	    src/ft_put/ft_putnbr_fd.c\
	    src/ft_put/ft_putstr_fd.c\
	    src/ft_str/ft_split.c\
	    src/ft_str/ft_strchr.c\
	    src/ft_str/ft_strdup.c\
	    src/ft_str/ft_striteri.c\
	    src/ft_str/ft_strjoin.c\
	    src/ft_str/ft_strlcat.c\
	    src/ft_str/ft_strlcpy.c\
	    src/ft_str/ft_strlen.c\
	    src/ft_str/ft_strmapi.c\
	    src/ft_str/ft_strncmp.c\
	    src/ft_str/ft_strcmp.c\
	    src/ft_str/ft_strnstr.c\
	    src/ft_str/ft_strrchr.c\
	    src/ft_str/ft_strtrim.c\
	    src/ft_str/ft_substr.c\
	    src/ft_to/ft_atoi.c\
	    src/ft_to/ft_atol.c\
	    src/ft_to/ft_itoa.c\
	    src/ft_to/ft_tolower.c\
	    src/ft_to/ft_toupper.c\
	    src/gnl/get_next_line.c\
	    src/gnl/get_next_line_utils.c\
	    src/utils.c\

DIR_INCS		=	inc/
DIR_OBJS		=	.objs/
OBJS			=	$(patsubst %.c, $(DIR_OBJS)%.o, $(SRCS))
DEPS			=	$(patsubst %.c, $(DIR_OBJS)%.d, $(SRCS))
DEPS_FLAGS		=	-MMD -MP
CFLAGS			=	-Wall -Wextra -Werror
RM				=	rm -rf
AR				= 	ar rcs

all : $(NAME)

$(NAME) : $(OBJS)
		$(AR) $(NAME) $(OBJS)

clean :
		$(RM) $(DIR_OBJS)

fclean : clean
		$(RM) $(NAME)

re : fclean
	$(MAKE) all

-include $(DEPS)

$(DIR_OBJS)%.o : %.c
		mkdir -p $(shell dirname $@)
		$(CC) $(CFLAGS) $(DEPS_FLAGS) -I $(DIR_INCS) -c $< -o $@

.PHONY: all clean fclean re
