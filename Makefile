# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/21 14:59:58 by luicasad          #+#    #+#              #
#    Updated: 2024/04/15 13:27:47 by luicasad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Here, rR is equivalent to --no-builtin-rules --no-builtin-variables.
#MAKEFLAGS += rR
#$(foreach x,$(filter-out .% MAKE% SHELL CURDIR,$(.VARIABLES)) MAKEINFO,$(if $(filter default,$(origin $x)),$(eval override undefine $x)))
# ============================================================================ #
#                                 SHELL                                        #
# ============================================================================ #
#SHELL			=	/usr/bin/bash
# ============================================================================ #
#                                 COLORS                                       #
# ============================================================================ #
DEF_COLOR		=	\033[0;39m
GRAY			=	\033[0;90m
RED				=	\033[0;91m
GREEN			=	\033[0;92m
YELLOW			=	\033[0;93m
BLUE			=	\033[0;94m
MAGENTA			=	\033[0;95m
CYAN			=	\033[0;96m
WHITE			=	\033[0;97m
BLACK			=	\033[0;99m
ORANGE			=	\033[38;5;209m
BROWN			=	\033[38;2;184;143;29m
DARK_GRAY		=	\033[38;5;234m
MID_GRAY		=	\033[38;5;245m
DARK_GREEN		=	\033[38;2;75;179;82m
DARK_YELLOW		=	\033[38;5;143m
# ============================================================================ #
#                                 TARGETS                                      #
# ============================================================================ #

NAME 			= pipex
BONUS 			= bonus
# ============================================================================ #
#                                 FOLDERS                                      #
# ============================================================================ #
SRCDIR_PIPEX		= ./src/pipex/
SRCDIR_BONUS		= ./src/bonus/
SRCDIR_PRINT		= ./src/ftpri/
SRCDIR_LIBFT		= ./src/libft/
SRCDIR_ARGPA		= ./src/argpa/	
SRCDIR_ERROR		= ./src/error/	

OBJDIR 			= ./obj/
INCDIR 			= ./inc/
LIBDIR			= ./lib/
REQUIRED_DIRS	= $(OBJDIR) $(INCDIR) $(LIBDIR)
vpath %.a $(LIBDIR)
# ============================================================================ #
#                               COMPILER SETUP                                 #
# ============================================================================ #
CC 				= cc
WRNFL			= -Wall -Wextra -Werror #-fsanitize=address -fno-omit-frame-pointer
DBGFL			= -g3
CFLGS			= $(DBGFL) $(WRNFL) -c
HEADS			= -I$(INCDIR)
#LFLGS 			= -Wl,-v
LFLGS 			= #-fsanitize=address

# ============================================================================ #
#                              LIBRARIES SETUP                                 #
# ============================================================================ #
NAMELIBPRINTF 		= libftprintf.a
PATH_PRINT 		= $(addprefix $(SRCDIR_PRINT), $(NAMELIBPRINTF))
LOADLIBPRINTF 		= ftprintf

NAMELIBFT 		= libft.a
PATH_LIBFT 		= $(addprefix $(SRCDIR_LIBFT), $(NAMELIBFT))
LOADLIBFT 		= ft

NAMELIBARGPA 		= libargpar.a
PATH_ARGPA 		= $(addprefix $(SRCDIR_ARGPA), $(NAMELIBARGPA))
LOADLIBARGPA 		= argpar

NAMELIBERROR 		= libfterror.a
PATH_ERROR 		= $(addprefix $(SRCDIR_ERROR), $(NAMELIBERROR))
LOADLIBERROR 		= fterror

MYLIBS			= $(NAMELIBPRINTF) $(NAMELIBFT) $(NAMELIBARGPA) $(NAMELIBERROR)
LLIBS 			= -L$(LIBDIR) -l$(LOADLIBARGPA) -l$(LOADLIBPRINTF) -l$(LOADLIBERROR) -l$(LOADLIBFT) 
LLIBS_BONUS		= -L$(LIBDIR) -l$(LOADLIBERROR) -l$(LOADLIBFT) -l$(LOADLIBPRINTF) 
# ============================================================================ #
#                                 SOURCES                                      #
# ============================================================================ #

HEADER		=	pipex.h
SRCS_PIPEX	= 	execute.c \
				create.c \
				destroy.c \
				cmd_create.c \
				cmd_destroy.c \
				read_or_exit.c \
				write_or_exit.c \
				show_pipex_args.c \
				set_file.c \
				pipex.c


FILE_PIPEX = $(addprefix $(SRCDIR_PIPEX), $(SRCS_PIPEX))

OBJS_PIPEX = $(addprefix $(OBJDIR), $(SRCS_PIPEX:.c=.o))

DEPE_PIPEX = $(addprefix $(OBJDIR), $(SRCS_PIPEX:.c=.d))

HEADER_BON	=	pipex_bonus.h
SRCS_BONUS	= 	execute_bonus.c \
				create_bonus.c \
				destroy_bonus.c \
				cmd_create_bonus.c \
				cmd_destroy_bonus.c \
				show_pipex_args_bonus.c \
				set_file_bonus.c \
				pipex_bonus.c \
				arg_find_point_slash_bonus.c \
				arg_fin_com_bonus.c \
				arg_fin_env_var_bonus.c \
				arg_is_command_bonus.c \
				arg_is_in_file_bonus.c \
				arg_is_ou_file_bonus.c \
				arg_val_var_bonus.c \
				arg_ok_bonus.c
				#open_or_exit_bonus.c \

FILE_BONUS = $(addprefix $(SRCDIR_BONUS), $(SRCS_BONUS))

OBJS_BONUS = $(addprefix $(OBJDIR), $(SRCS_BONUS:.c=.o))

DEPE_BONUS = $(addprefix $(OBJDIR), $(SRCS_BONUS:.c=.d))

#$(info source files $(SRCS_PIPEX))
#$(info source paths $(FILE_PIPEX))
#$(info object patha $(OBJS_PIPEX))
#$(info depend patha $(DEPE_PIPEX))
# ============================================================================ #
#                                 RULES                                        #
# ============================================================================ #
all: makedirs makelibs $(NAME)
#includes all dependencies files.
#READ GNU make  manual 4.14 Generating Prerequisites Automatically.
-include $(DEPE_PIPEX)


bonus: makedirs makelibs $(BONUS)
-include $(DEPE_BONUS)
# .......................... directories creation ............................ #

makedirs:
	$(shell for d in $(REQUIRED_DIRS); \
 				do \
 					[[ -d $$d ]] || mkdir -p $$d; \
 				done)

# .......................... library construction ............................ #
makelibs: $(MYLIBS) 

$(NAMELIBPRINTF): makelibftprintf $(LIBDIR)$(NAMELIBPRINTF)
$(NAMELIBFT): 	  makelibft $(LIBDIR)$(NAMELIBFT)
$(NAMELIBARGPA):  makelibargpa $(LIBDIR)$(NAMELIBARGPA)
$(NAMELIBERROR):  makeliberror $(LIBDIR)$(NAMELIBERROR)

-lft:makelibft
-lftprintf:makelibftprintf
-largpar:makelibargpa
-lfterror:makeliberror

makelibft: 
	$(MAKE) -C $(SRCDIR_LIBFT)

makelibftprintf:
	$(MAKE) -C $(SRCDIR_PRINT)

makelibargpa:
	$(MAKE) -C $(SRCDIR_ARGPA)

makeliberror:
	$(MAKE) -C $(SRCDIR_ERROR)

# ....................... dependencies construction .......................... #
#for each c file create its dependency file 
#READ GNU make  manual 4.14 Generating Prerequisites Automatically.
#READ GNU gcc manuel 3.13 Options controlling the preprocessor.
%.d: %.c
	@set -e; rm -f $@; \
	$(CC) $(HEADS) -MM $< > $@.$$$$ ; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
    rm -f $@.$$$$
# .......................... targets construction ............................ #
$(NAME): Makefile  $(OBJS_PIPEX) -l$(LOADLIBFT) -l$(LOADLIBPRINTF) -l$(LOADLIBARGPA) -l$(LOADLIBERROR) 
	@echo "$(GREEN)========== GATHERING PIPEX OBJECTS =============$(DEF_COLOR)"
	$(CC) $(LFLGS) $(OBJS_PIPEX) -o $@ $(LLIBS)

$(BONUS): Makefile $(OBJS_BONUS) -l$(LOADLIBFT) -l$(LOADLIBPRINTF) -l$(LOADLIBERROR)  
	@echo "$(MAGENTA)========== GATHERING CHECKER OBJECTS ===============$(DEF_COLOR)"
	$(CC) $(LFLGS) $(OBJS_BONUS) -o $@ $(LLIBS_BONUS)
# .......................... objects construction ............................ #
$(OBJDIR)%.o: $(SRCDIR_PIPEX)%.c $(INCDIR)$(HEADER)
	@echo "$(GREEN)========== COMPILING PIPEX FILES ===============$(DEF_COLOR)"
	$(CC) $(CFLGS) $< -o $@ $(HEADS)  
 
$(OBJDIR)%.o: $(SRCDIR_BONUS)%.c $(INCDIR)$(HEADER_BON)
	@echo "$(GREEN)========== COMPILING BONUS FILES ===============$(DEF_COLOR)"
	$(CC) $(CFLGS) $< -o $@ $(HEADS)  

.PHONY: clean
clean:
	@echo "========== Cleaning pipex objects =============="
	rm -f $(OBJS_PIPEX)
	@echo "========== Cleaning prinf_f objects ================"
	$(MAKE) -C $(SRCDIR_PRINT)  clean
	@echo "========== Cleaning libft  objects ================="
	$(MAKE) -C $(SRCDIR_LIBFT)  clean
	@echo "========== Cleaning argpa  objects ================="
	$(MAKE) -C $(SRCDIR_ARGPA)  clean
	@echo "========== Cleaning error  objects ================="
	$(MAKE) -C $(SRCDIR_ERROR)  clean
	@echo "========== Cleaning libraries *.a =================="
	rm -f $(LIBDIR)*

.PHONY: fclean
fclean : clean
	@echo "========== Cleaning executable Push_Swap ==========="
	rm -f $(NAME)
	@echo "======= Cleaning prinf_f objects and library ======="
	$(MAKE) -C $(SRCDIR_PRINT)  fclean
	@echo "======= Cleaning libft   objectsand library ========"
	$(MAKE) -C $(SRCDIR_LIBFT)  fclean
	@echo "======= Cleaning argpa   objectsand library ========"
	$(MAKE) -C $(SRCDIR_ARGPA)  fclean
	@echo "======= Cleaning error   objectsand library ========"
	$(MAKE) -C $(SRCDIR_ERROR)  fclean

.PHONY: re
re: fclean all
	@echo "========== Rebuilding pipex ===================="

.PHONY: bonus_clean
bonus_clean:
	@echo "========== Cleaning pipex bonus objects ================"
	rm -f $(OBJS_BONUS)

.PHONY: bonus_fclean
bonus_fclean: bonus_clean
	@echo "========== Cleaning executable pipex bonus ============="
	rm -f $(BONUS)
norma:
	$(MAKE) -C $(SRCDIR_PRINT)  norma
	$(MAKE) -C $(SRCDIR_LIBFT)  norma
	$(MAKE) -C $(SRCDIR_ARGPA)  norma
	$(MAKE) -C $(SRCDIR_ERROR)  norma
	@echo "$(GREEN)========== CHECKING NORME $(NAME) ==============$(DEF_COLOR)"
	norminette $(SRCDIR_PIPEX) 
	@echo "$(MAGENTA)========== CHECKING NORME $(BONUS) ==============$(DEF_COLOR)"
	norminette $(SRCDIR_BONUS)
	norminette $(INCDIR)
run:
	valgrind -s --tool=memcheck --leak-check=full --track-origins=yes --track-fds=yes --trace-children=yes ./$(NAME) $(VAR)
bonusrun:
	#valgrind -s --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children=yes ./$(BONUS) $(VAR)
	#valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes ./$(BONUS) $(VAR)
	valgrind --track-fds=yes --trace-children=yes ./$(BONUS) $(VAR)
bonusrung:
	valgrind --tool=massif --stacks=yes ./$(BONUS)
