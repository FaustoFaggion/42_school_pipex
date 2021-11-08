#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

//2 proccess
//1 Child proccess generate random numbers and sent to the parents
//2 parent is going to sum all numbers and print the sum

int	main(void)
{
	int		pid;
	int		arr[10];
	int		n;
	int		i;
	int		fd[2];
	int		sum;

	if (pipe(fd) == -1)
		return (2);

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0) // child
	{
		close(fd[0]);
		srand(time(NULL));
		n = rand() % 10 + 1;
		i = 0;
		while (i < n)
		{
			arr[i] = rand() % 11;
			i++;
		}
		if (write(fd[1], &n, sizeof(int)) < 0)
			return (3);
		printf("Sending n: %d \n", n);
		if (write(fd[1], arr, sizeof(int) * n) < 0)
			return (4);
		printf("Sending arr \n");
		i = 0;
		while (i < n)
		{
			printf("%d, ", arr[i]);
			i++;
		}
		printf("\n");
		close(fd[1]);
	}
	else //parent
	{
		wait(NULL);
		close(fd[1]);
		if (read(fd[0], &n, sizeof(int)) < 0)
			return (5);
		printf("n readed: %d\n", n);
		if (read(fd[0], arr, sizeof(int) * n) < 0)
			return (6);
		printf("array readed \n");
		i = 0;
		while (i < n)
		{
			printf("%d,", arr[i]);
			i++;
		}
		close(fd[0]);
		i = 0;
		while (i < n)
		{
			sum += arr[i];
			i++;
		}
		printf("\n");
		printf("Resultado soma: %d\n", sum);
	}
	return (0);
}
