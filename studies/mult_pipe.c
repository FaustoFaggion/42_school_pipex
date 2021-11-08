#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

// parent send x to child
// child1 send x+5 to child2
// child2 send x+5 to parent

int	main(void)
{
	int		fd[3][2];
	int		i;
	int		x;
	int		pid1;
	int		pid2;

	i= 0;
	while(i < 3)
	{
		if (pipe(fd[i]) < 0)
			return (1);
		i++;
	}

	pid1 = fork();
	if (pid1 < 0)
		return (2);
	
	if (pid1 == 0) //child 1
	{
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[2][0]);
		close(fd[2][1]);
		if (read(fd[0][0], &x, sizeof(int)) < 0)
			return (3);
		x += 5;
		if (write(fd[1][1], &x, sizeof(int)) < 0)
			return (3);
		close(fd[0][0]);
		close(fd[1][0]);
		return (0);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (4);
	
	if (pid2 == 0)
	{
		close(fd[1][1]);
		close(fd[2][0]);
		close(fd[0][0]);
		close(fd[0][1]);
		if (read(fd[1][0], &x, sizeof(int)) < 0)
			return (5);
		x += 5;
		if (write(fd[2][1], &x, sizeof(int)) < 0)
			return (6);
		close(fd[1][0]);
		close(fd[2][1]);
		return (0);
	}
	// parent
	close(fd[2][1]);
	close(fd[0][0]);
	close(fd[1][0]);
	close(fd[1][1]);
	x = 0;
	if (write(fd[0][1], &x, sizeof(int)) < 0)
		return (9);
	if (read(fd[2][0], &x, sizeof(int)) < 0)
		return (8);

	printf("result is: %d\n", x);

	close(fd[0][0]);
	close(fd[0][1]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}