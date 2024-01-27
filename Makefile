# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/16 18:17:45 by sguzman           #+#    #+#              #
#    Updated: 2024/01/27 02:27:27 by sguzman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                     CONFIG                                   #
################################################################################

NAME		= fdf
CC 		= gcc
CFLAGS		= -Wall -Wextra -Werror -lXext -lX11
DFLAGS		= -MMD -MF $(@:.o=.d)
UNAME 		= $(shell uname)

ifeq ($(UNAME), Darwin)
	MLXFLAGS = -framework OpenGL -framework AppKit -lm
endif
ifeq ($(UNAME), Linux)
	MLXFLAGS = -lX11 -lXext -lm 
endif

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS_PATH	= ./src

OBJS_PATH 	= ./build

GNL_PATH	= $(SRCS_PATH)/get_next_line

INCLUDE_PATH	= ./include

LIBFTPRINTF_PATH = ./libs/libftprintf

MINILIBX_PATH    = ./libs/minilibx

LIBFTPRINTF		= $(LIBFTPRINTF_PATH)/libftprintf.a

MINILIBX	=	$(MINILIBX_PATH)/libmlx.a $(MINILIBX_PATH)/libmlx_$(UNAME).a

HEADER		= $(INCLUDE_PATH)/fdf.h

GNL_HEADER 	= $(GNL_PATH)/get_next_line.h

SRCS 		= clean.c parse.c  render.c 

GNL_SRCS 	= get_next_line.c get_next_line_utils.c

MAIN 		= fdf.c 

################################################################################
#                                  Makefile  objs                              #
################################################################################

OBJS		= $(addprefix $(OBJS_PATH)/, ${SRCS:.c=.o})

GNL_OBJS	= $(addprefix $(OBJS_PATH)/, ${GNL_SRCS:.c=.o})

OBJS_MAIN	= $(addprefix $(OBJS_PATH)/, ${MAIN:.c=.o})

DEPS		= $(addprefix $(OBJS_PATH)/, ${SRCS:.c=.d})

GNL_DEPS	= $(addprefix $(OBJS_PATH)/, ${GNL_SRCS:.c=.d})

DEPS_MAIN	= $(addprefix $(OBJS_PATH)/, ${MAIN:.c=.d})

################################################################################
#                                 Makefile logic                               #
################################################################################

RED         	= \033[0;31m
GREEN       	= \033[0;32m
YELLOW      	= \033[0;33m
BLUE        	= \033[0;34m
PURPLE      	= \033[0;35m
CYAN        	= \033[0;36m
RESET       	= \033[m

################################################################################
#                                 Makefile rules                               #
################################################################################

all: banner $(NAME) 

banner:
	@printf "%b" "$(PURPLE)"
	@echo
	@echo "# **************************************************************************** #"
	@echo "#                                                                              #"
	@echo "#                                                         :::      ::::::::    #"
	@echo "#    FDF                                                :+:      :+:    :+:    #"
	@echo "#                                                     +:+ +:+         +:+      #"
	@echo "#    By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+         #"
	@echo "#                                                 +#+#+#+#+#+   +#+            #"
	@echo "#                                                      #+#    #+#              #"
	@echo "#                                                     ###   ########.fr        #"
	@echo "#                                                                              #"
	@echo "# **************************************************************************** #"
	@echo
	@printf "%b" "$(RESET)"

-include $(DEPS) $(GNL_DEPS) $(DEPS_MAIN)
$(NAME):	$(OBJS) $(GNL_OBJS) $(OBJS_MAIN) $(LIBFTPRINTF) $(MINILIBX)
			@$(CC) $(CFLAGS) $(DFLAGS) -I $(INCLUDE_PATH) $^ $(MLXFLAGS) -o $@ 
			@printf "%b%-42s%-42b%-24s%b%s%b\n" "$(BLUE)" "Building program:" "$(CYAN)" $@ "$(GREEN)" "[✓]" "$(RESET)"

$(LIBFTPRINTF):
			@make -C $(LIBFTPRINTF_PATH) > /dev/null
			@printf "%b%-42s%-42b%-24s%b%s%b\n" "$(BLUE)" "Building Libftprintf library:" "$(CYAN)" $@ "$(GREEN)" "[✓]" "$(RESET)"

$(MINILIBX):
			@make -C $(MINILIBX_PATH) > /dev/null
			@printf "%b%-42s%-42b%-24s%b%s%b\n" "$(BLUE)" "Building Minilibx library:" "$(CYAN)" $@ "$(GREEN)" "[✓]" "$(RESET)"

$(OBJS_PATH)/%.o: 	$(SRCS_PATH)/%.c $(HEADER) Makefile
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@ -I $(INCLUDE_PATH)
			@printf "%b%-42s%-42b%-24s%b%s%b\n" "$(BLUE)" "Compiling:" "$(CYAN)" $< "$(GREEN)" "[✓]" "$(RESET)"

$(OBJS_PATH)/%.o: 	$(GNL_PATH)/%.c $(GNL_HEADER) Makefile
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@ -I $(GNL_PATH)
			@printf "%b%-42s%-42b%-24s%b%s%b\n" "$(BLUE)" "Compiling:" "$(CYAN)" $< "$(GREEN)" "[✓]" "$(RESET)"

clean:		banner
			@rm -rf $(OBJS_PATH)
			@printf "%b%-42s%-42b%b%s%b\n" "$(BLUE)" "$@:" "$(CYAN)" "$(GREEN)" "[✓]" "$(RESET)"

fclean:		banner clean
			@rm -rf $(NAME)
			@printf "%b%-42s%-42b%b%s%b\n" "$(BLUE)" "$@:" "$(CYAN)" "$(GREEN)" "[✓]" "$(RESET)"

re:			fclean all

.PHONY:		all clean fclean re banner 
