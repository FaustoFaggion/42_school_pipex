NAME			=	pipex
NAME_BONUS		=	pipex_bonus

I_LIBFT			=	-I ./libft
I_PIPEX			=	-I ./include

CC				=	clang
CFLAGS			=	-Wall -Werror -Wextra -g

SRC_DIR			=	sources
SRC_FILES		=	pipex.c \
					pipex_utils.c \
					ft_split_shell.c \
					ft_strjoin.c \
					ft_strlen.c \
					ft_strlcpy.c \
					ft_strncmp.c \
					ft_substr.c \
					ft_strdup.c

SRC				=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))

SRC_DIR_BONUS	=	sources_bonus
SRC_FILES_BONUS	=	pipex_bonus.c \
					pipex_utils_bonus.c \
					ft_split_shell_bonus.c \
					here_doc.c \
					ft_strjoin.c \
					ft_strlen.c \
					ft_strlcpy.c \
					ft_strncmp.c \
					ft_substr.c \
					ft_strdup.c \
					ft_get_next_line.c \
					ft_strchr.c

SRC_BONUS		=	$(addprefix $(SRC_DIR_BONUS)/, $(SRC_FILES_BONUS))

OBJ_DIR			=	objects
OBJ				=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJ_DIR_BONUS	=	objects_bonus
OBJ_BONUS		=	$(SRC_BONUS:$(SRC_DIR_BONUS)/%.c=$(OBJ_DIR_BONUS)/%.o)

FS				=	-fsanitize=address -g3

all:	$(NAME)

bonus:	$(NAME_BONUS)

$(NAME):	$(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(I_PIPEX)

$(NAME_BONUS):	$(OBJ_DIR_BONUS) $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME_BONUS) $(I_PIPEX)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(I_PIPEX)

$(OBJ_DIR_BONUS)/%.o:	$(SRC_DIR_BONUS)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(I_PIPEX)

$(OBJ_DIR):
	mkdir objects

$(OBJ_DIR_BONUS):
	mkdir objects_bonus

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_BONUS)
	rm -rf $(OBJ_DIR_BONUS)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME_BONUS)

re: fclean all

run:
	make && ./pipex file1.txt "wc -l" "cat" file2.txt

run_bonus:
	make bonus && ./pipex_bonus file1.txt "tr a Z" "tr e c" file2.txt

sanitize:	$(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(FS) $(OBJ) -o $(NAME) $(I_PIPEX)
	./pipex file1.txt "tr a b" "tr e c" file2.txt

valgrind:
	make && valgrind --leak-check=full --show-leak-kinds=all ./pipex file1.txt "tr a b" "tr e f" file2.txt

valgrind_bonus: $(NAME_BONUS)
	make bonus && valgrind --leak-check=full --show-leak-kinds=all ./pipex_bonus file1.txt "tr a b" "tr e c" file2.txt
