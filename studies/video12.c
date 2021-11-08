#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main (int argc, char *argv[])
{
	int	pid;
	int	err;
	int	wstatus;
	int status_code;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0) // child proccess
	{
		err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
		if (err == -1)
		{
			printf("Could not find a program to exe.\n");
			return (2);
		}
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