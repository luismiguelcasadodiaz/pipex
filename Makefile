# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luicasad <luicasad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/21 14:59:58 by luicasad          #+#    #+#              #
#    Updated: 2024/02/20 19:01:46 by luicasad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Here, rR is equivalent to --no-builtin-rules --no-builtin-variables.
#MAKEFLAGS += rR
#$(foreach x,$(filter-out .% MAKE% SHELL CURDIR,$(.VARIABLES)) MAKEINFO,$(if $(filter default,$(origin $x)),$(eval override undefine $x)))
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
SRCDIR_PRINT		= ./src/ftpri/
SRCDIR_LIBFT		= ./src/libft/
SRCDIR_ARGPA		= ./src/argpa/	

OBJDIR 			= ./obj/
INCDIR 			= ./inc/
LIBDIR			= ./lib/
REQUIRED_DIRS	= $(OBJDIR) $(INCDIR) $(LIBDIR)
vpath %.a $(LIBDIR)
# ============================================================================ #
#                               COMPILER SETUP                                 #
# ============================================================================ #
CC 				= cc
WRNFL			= -Wall -Wextra -Werror -fsanitize=address
DBGFL			= -g3
CFLGS			= $(DBGFL) $(WRNFL) -c
HEADS			= -I$(INCDIR)
#LFLGS 			= -Wl,-v
LFLGS 			= -fsanitize=address

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

MYLIBS			= $(NAMELIBPRINTF) $(NAMELIBFT) $(NAMELIBARGPA)
LLIBS 			= -L$(LIBDIR) -l$(LOADLIBARGPA) -l$(LOADLIBPRINTF) -l$(LOADLIBFT) 
# ============================================================================ #
#                                 SOURCES                                      #
# ============================================================================ #

HEADER		=	pipex.h
SRCS_PIPEX	= 	execute.c \
				show_pipex_args.c \
				pipex.c


FILE_PIPEX = $(addprefix $(SRCDIR_PIPEX), $(SRCS_PIPEX))

OBJS_PIPEX = $(addprefix $(OBJDIR), $(SRCS_PIPEX:.c=.o))

DEPE_PIPEX = $(addprefix $(OBJDIR), $(SRCS_PIPEX:.c=.d))

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


#bonus: makedirs makelibs $(BONUS)
#-include $(DEPE_CHECK)
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

makelibft: 
	$(MAKE) -C $(SRCDIR_LIBFT)

makelibftprintf:
	$(MAKE) -C $(SRCDIR_PRINT)

makelibargpa:
	$(MAKE) -C $(SRCDIR_ARGPA)

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
$(NAME): Makefile  $(OBJS_PIPEX) -l$(LOADLIBFT) -l$(LOADLIBPRINTF) -l$(LOADLIBARGPA) 
	@echo "$(GREEN)========== GATHERING PUSH_SWAP OBJECTS =============$(DEF_COLOR)"
	$(CC) $(LFLGS) $(OBJS_PIPEX) -o $@ $(LLIBS)

#$(BONUS): Makefile $(OBJS_CHECK) -l$(LOADLIBFT) -l$(LOADLIBPRINTF) -l$(LOADLIBSS) -l$(LOADLIBARGPA) 
#	@echo "$(MAGENTA)========== GATHERING CHECKER OBJECTS ===============$(DEF_COLOR)"
#	$(CC) $(LFLGS) $(OBJS_CHECK) -o $@ $(LLIBS)
# .......................... objects construction ............................ #
$(OBJDIR)%.o: $(SRCDIR_PIPEX)%.c $(INCDIR)$(HEADER)
	@echo "$(GREEN)========== COMPILING PUSH_SWAP FILES ===============$(DEF_COLOR)"
	$(CC) $(CFLGS) $< -o $@ $(HEADS)  
 
.PHONY: clean
clean:
	@echo "========== Cleaning Push_swap objects =============="
	rm -f $(OBJS_PIPEX)
	@echo "========== Cleaning prinf_f objects ================"
	$(MAKE) -C $(SRCDIR_PRINT)  clean
	@echo "========== Cleaning libft  objects ================="
	$(MAKE) -C $(SRCDIR_LIBFT)  clean
	@echo "========== Cleaning libpss  objects ================="
	$(MAKE) -C $(SRCDIR_STACK)  clean
	@echo "========== Cleaning libpss  objects ================="
	$(MAKE) -C $(SRCDIR_ARGPA)  clean
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
	@echo "======= Cleaning libft   objectsand library ========"
	$(MAKE) -C $(SRCDIR_STACK)  fclean
	@echo "======= Cleaning libft   objectsand library ========"
	$(MAKE) -C $(SRCDIR_ARGPA)  fclean

.PHONY: re
re: fclean all
	@echo "========== Rebuilding Push_swap ===================="

.PHONY: bonus_clean
bonus_clean:
	@echo "========== Cleaning CHECKER objects ================"
	rm -f $(OBJS_CHECK)

.PHONY: bonus_fclean
bonus_fclean: bonus_clean
	@echo "========== Cleaning executable Checker ============="
	rm -f $(BONUS)
norma:
	$(MAKE) -C $(SRCDIR_PRINT)  norma
	$(MAKE) -C $(SRCDIR_LIBFT)  norma
	$(MAKE) -C $(SRCDIR_ARGPA)  norma
	@echo "$(GREEN)========== CHECKING NORME $(NAME) ==============$(DEF_COLOR)"
	norminette $(SRCDIR_PIPEX) 
	@echo "$(MAGENTA)========== CHECKING NORME $(BONUS) ==============$(DEF_COLOR)"
	norminette $(SRCDIR_CHECK)
run:
	valgrind --tool=memcheck --leak-check=yes ./$(NAME)
bonusrun:
	valgrind --tool=memcheck --leak-check=yes ./$(BONUS)
bonusrung:
	valgrind --tool=massif --stacks=yes ./$(BONUS)
