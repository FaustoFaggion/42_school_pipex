NAME			=	pipex
#NAME_BONUS		=	pipex_bonus

PATH_LIBFT		=	./libft
LIBFT			=	$(PATH_LIBFT)/libft.a

I_LIBFT			=	-I ./libft
I_PIPEX			=	-I ./include

CC				=	clang
CFLAGS			=	-Wall -Werror -Wextra -g

SRC_DIR			=	sources
SRC_FILES		=	pipex.c

SRC				=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))

#SRC_DIR_BONUS	=	sources_bonus
#SRC_FILES_BONUS	=
#SRC_BONUS		=	$(addprefix $(SRC_DIR_BONUS)/, $(SRC_FILES_BONUS))

OBJ_DIR			=	objects
OBJ				=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#OBJ_DIR_BONUS	=	objects_bonus
#OBJ_BONUS		=	$(SRC_BONUS:$(SRC_DIR_BONUS)/%.c=$(OBJ_DIR_BONUS)/%.o)

HEADER			=	pipex.h
#HEADER_BONUS	=	pipex_bonus.h

FS				=	-fsanitize=address -g3

all:	$(NAME)

#bonus:	$(NAME_BONUS)

$(NAME):	$(LIBFT) $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(I_PIPEX) $(I_LIBFT)

#$(NAME_BONUS):	$(LIBFT) $(OBJ_DIR_BONUS) $(OBJ_BONUS) $(HEADER_BONUS)
#	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME_BONUS)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(I_PIPEX) $(I_LIBFT)

#$(OBJ_DIR_BONUS)/%.o:	$(SRC_DIR_BONUS)/%.c $(HEADER_BONUS)
#	$(CC) $(CFLAGS) -c $< -o $@ $(I_OBJ)

$(LIBFT):
	make -C $(PATH_LIBFT)

$(OBJ_DIR):
	mkdir objects

#$(OBJ_DIR_BONUS):
#	mkdir objects_bonus

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_DIR)
#	rm -rf $(OBJ_BONUS)
#	rm -rf $(OBJ_DIR_BONUS)
	make -C $(PATH_LIBFT) clean

fclean: clean
	rm -rf $(NAME)
#	rm -rf $(NAME_BONUS)
	make -C $(PATH_LIBFT) fclean

re: fclean all

run:
	make && ./pipex file1.txt "tr a b" "tr e c" file2.txt

#run_bonus:


sanitize:	$(LIBFT) $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(FS) $(OBJ) $(LIBFT) -o $(NAME) $(I_PIPEX) $(I_LIBFT)
	./pipex file1.txt "tr a b" "tr e c" file2.txt

valgrind:
	make && valgrind ./pipex file1.txt "tr a b" "tr e c" file2.txt

#valgrind_bonus: $(NAME_BONUS)
	valgrind --leak-check=full --show-leak-kinds=all ./pipex file1.txt "tr a b" "tr e c" file2.txt
