#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

//Redirecting standard output
int main (void)
{
	int	pid;
	int	err;
	int	wstatus;
	int status_code;
	int fd1;
	int fd2;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0) // child proccess
	{
		fd1 = open("file3.txt", O_WRONLY);
		if (fd1 == -1)
			return(2);
		printf("fd1: %d\n", fd1);
		fd2 = dup2(fd1, STDOUT_FILENO);	
		printf("fd2: %d\n", fd2);
		close(fd1);
		err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
		if (err == -1)
		{
			printf("Could not find a program to exe.\n");
			return (3);
		}
		close(fd2);
	}
	else // parent proccess
	{
		wait(&wstatus);
		if (WIFEXITED(wstatus))
		{
			status_code = WEXITSTATUS(wstatus);
			if (status_code == 0)
				printf("Success!!\n");
			else
				printf("failure with status_code : %d!!\n", status_code);
		}
	}
	return (0);
}