#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

//executing commands
int main (int argc, char *argv[])
{
	int pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0) // child proccess
		execlp("ping", "ping", "-c", "3", "google.com", NULL);
	else // parent proccess
	{
		wait(NULL);
		printf("Success!!");
	}
	return (0);
}