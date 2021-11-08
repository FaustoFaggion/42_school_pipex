#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

// ping -c 5 google.com | grep rtt
// | it is a pipe
int	main(void)
{
	int		fd[2];
	int		pid1;
	int		pid2;

	if (pipe(fd) == -1)
		return (1);

	pid1 = fork();
	if (pid1 < 0)
		return (2);
	
	if (pid1 == 0) //child (ping)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (execlp("ping", "ping", "-c", "5", "google.com", NULL) < 0)
			return (3);
	}

	pid2 = fork();
	if (pid2 < 0)
			return (4);
	
	if (pid2 == 0) // child grep
	{
		waitpid(pid1, NULL, 0);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (execlp("grep", "grep", "PING", NULL) < 0)
			return (5);

	}
	//parent
	close(fd[0]);
	close(fd[1]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}