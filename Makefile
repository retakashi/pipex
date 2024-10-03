NAME = pipex
BONUS_NAME = pipex_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
GNL = ../gnl/get_next_line.c ../gnl/get_next_line_utils.c
SRCS = mandatory.c pipex_utils.c error.c child.c
BONUS_SRCS = heredoc.c bonus.c child.c pipex_utils.c error.c $(GNL)
OBJS_DIR = objs
OBJS = ${addprefix $(OBJS_DIR)/,$(SRCS:.c=.o)}
BONUS_OBJS = ${addprefix $(OBJS_DIR)/,$(BONUS_SRCS:.c=.o)}

ifdef WITH_BONUS
	$(OBJS) = $(BONUS_OBJS)
else
	$(OBJS) = $(OBJS)
endif

RM = rm -f

.DEFAULT_GOAL :=$(NAME)

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
${OBJS_DIR}/%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	make clean -C libft
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME) $(LIBFT) $(BONUS_NAME) $(GNL)
	
re: fclean all

$(BONUS_NAME): $(BONUS_OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS_NAME)
	
bonus: $(BONUS_NAME)
@make WITH_BONUS=1

.PHONY: all clean fclean re bonus
