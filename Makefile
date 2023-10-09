NAME		:=	philo

CC			:=	clang -Wall -Wextra -Werror
FLAGS		:=	-lpthread
FLAGS		+=	-g -fsanitize=thread

DIR_SRCS	:=	srcs
DIR_OBJS	:=	.objs
DIR_INCS	:=	include

SRCS	:=	death.c \
				forks.c \
				init.c \
				life.c \
				main.c \
				threads.c \
				utils.c
OBJS	:=	$(SRCS:.c=.o)
INCL	:=	philosophers.h

SRCS		:=	$(addprefix $(DIR_SRCS)/, $(SRCS))
OBJS		:=	$(addprefix $(DIR_OBJS)/, $(OBJS))
INCL		:=	$(addprefix $(DIR_INCS)/, $(INCL))

ERASE		:=	\033[2K\r
BLUE		:=	\033[34m
YELLOW		:=	\033[33m
GREEN		:=	\033[32m
END			:=	\033[0m

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c $(INCS)
	mkdir -p $(DIR_OBJS)
	$(CC) -I $(DIR_INCS) -c $< -o $@
	printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

all:		$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o $@
	printf "$(ERASE)$(GREEN)$@ made\n$(END)"

clean:
	printf "$(YELLOW)$(DIR_OBJS) removed$(END)\n"
	rm -rdf $(DIR_OBJS)

fclean:		clean
	printf "$(YELLOW)$(NAME) removed$(END)\n"
	rm -rf $(NAME) checker

re:			fclean all

usage:
			@echo "Usage: make [usage | all | philo | clean | fclean | re]"