NAME			= philo

SRCS			= main.c \
				  ft_atoi.c \
				  philo_n_forks.c \
				  onlyonephilo.c \
				  what_time_is_it.c \
				  philosophers_doing_stuff.c \
				  create_threads.c  \
				  execution.c \
				  checker.c 
				  

OBJS			= $(SRCS:.c=.o)

OBJDIR	=	objs
SRCDIR	=	srcs

OBJS	=	$(addprefix ${OBJDIR}/, ${SRCS:.c=.o})

CC				= gcc -pthread
RM				= rm -rf

CFLAGS			= -Wall -Wextra -Werror #-g3 -fsanitize=thread
INCL			= includes
LIBS			= -lpthread



${OBJDIR}/%.o: ${SRCDIR}/%.c
			mkdir -p ${@D}
			${CC} ${CFLAGS} -I${INCL} -c $< -o $@

$(NAME):		$(OBJS)
				${CC} ${CFLAGS} ${OBJS} -o ${NAME} ${LIBS}

all:			$(NAME)

clean:
				${RM} ${OBJDIR}

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)
				$(MAKE) all -j


.PHONY:			all clean fclean re
