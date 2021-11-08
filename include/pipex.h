#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h> //wait()
# include "libft.h"

# define path_file1		"./file1.txt"
# define path_file2		"./file2.txt"

#endif


//fd[0][0] = read parent
//fd[0][1] = write parent
//fd[1][0] = read pd1
//fd[1][1] = write pd1