#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>

//Redirecting standard output
int main (void)
{
	int		pid;
	int		t;

	pid = fork();
	if (pid == -1)
		return (1);

	if (pid == 0) // child proccess
	{
		while (1)
		{
			printf("Some text come here!!\n");
			usleep(50000);
		}

	}
	else // parent proccess
	{
		kill(pid, SIGSTOP);
		while (t > 0)
		{
			printf("Time in seconds for execution: ");
			scanf("%d", &t);
			if (t > 0)
			{	
				kill(pid, SIGCONT);
				sleep(t);
				kill(pid, SIGSTOP);
			}
		}
		kill(pid, SIGKILL);
		wait(NULL);
	}
	return (0);
}