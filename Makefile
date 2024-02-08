# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/16 18:17:45 by sguzman           #+#    #+#              #
#    Updated: 2024/02/08 02:30:51 by sguzman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                     CONFIG                                   #
################################################################################

NAME		= fdf
CC 		= cc
CFLAGS		= -Wall -Wextra -Werror -g -fsanitize=address
DFLAGS		= -MMD -MF $(@:.o=.d)
UNAME 		= $(shell uname)

ifeq ($(UNAME), Darwin)
	MLXFLAGS = -framework Cocoa -framework OpenGL -framework IOKit
endif
ifeq ($(UNAME), Linux)
	MLXFLAGS = -ldl -lglfw -pthread -lm
endif

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS_PATH	= ./src

OBJS_PATH 	= ./build

GNL_PATH	= $(SRCS_PATH)/get_next_line

INCLUDE_PATH	= ./include

LIBFTPRINTF_PATH = ./libs/libftprintf

MLX_PATH    = ./libs/MLX42

LIBFTPRINTF		= $(LIBFTPRINTF_PATH)/libftprintf.a

MLX	=	$(MLX_PATH)/build/libmlx42.a

HEADER		= $(INCLUDE_PATH)/fdf.h

GNL_HEADER 	= $(GNL_PATH)/get_next_line.h

SRCS 		= clean.c graphics.c parse.c render.c transform.c

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
$(NAME):	$(OBJS) $(GNL_OBJS) $(OBJS_MAIN) $(LIBFTPRINTF) $(MLX)
			@$(CC) $(CFLAGS) $(DFLAGS) -I $(INCLUDE_PATH) $^ $(MLXFLAGS) -o $@ 
			@printf "%b%-42s%-42b%-24s%b%s%b\n" "$(BLUE)" "Building program:" "$(CYAN)" $@ "$(GREEN)" "[✓]" "$(RESET)"

$(LIBFTPRINTF):
			@make bonus -C $(LIBFTPRINTF_PATH) > /dev/null
			@printf "%b%-42s%-42b%-24s%b%s%b\n" "$(BLUE)" "Building Libftprintf library:" "$(CYAN)" $@ "$(GREEN)" "[✓]" "$(RESET)"

$(MLX):
			@cmake $(MLX_PATH) -B $(MLX_PATH)/build > /dev/null && make -C $(MLX_PATH)/build  > /dev/null
			@printf "%b%-42s%-42b%-24s%b%s%b\n" "$(BLUE)" "Building Mlx library:" "$(CYAN)" $@ "$(GREEN)" "[✓]" "$(RESET)"

$(OBJS_PATH)/%.o: 	$(SRCS_PATH)/%.c $(HEADER) Makefile
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@ -I $(INCLUDE_PATH)
			@printf "%b%-42s%-42b%-24s%b%s%b\n" "$(BLUE)" "Compiling:" "$(CYAN)" $< "$(GREEN)" "[✓]" "$(RESET)"

$(OBJS_PATH)/%.o: 	$(GNL_PATH)/%.c $(GNL_HEADER) Makefile
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@ -I $(GNL_PATH)
			@printf "%b%-42s%-42b%-24s%b%s%b\n" "$(BLUE)" "Compiling:" "$(CYAN)" $< "$(GREEN)" "[✓]" "$(RESET)"

clean:		banner
			@make $@ -C $(LIBFTPRINTF_PATH) > /dev/null
			@make $@ -C $(MLX_PATH)/build > /dev/null
			@rm -rf $(OBJS_PATH)
			@printf "%b%-42s%-42b%b%s%b\n" "$(BLUE)" "$@:" "$(CYAN)" "$(GREEN)" "[✓]" "$(RESET)"

fclean:		banner clean
			@make $@ -C $(LIBFTPRINTF_PATH) > /dev/null
			@rm -rf $(NAME)
			@printf "%b%-42s%-42b%b%s%b\n" "$(BLUE)" "$@:" "$(CYAN)" "$(GREEN)" "[✓]" "$(RESET)"

re:			fclean all

.PHONY:		all clean fclean re banner $(MLX) $(LIBFTPRINTF)
