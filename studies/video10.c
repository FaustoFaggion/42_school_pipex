#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int	p1[2]; //child -> parent
	int	p2[2]; //parent -> child
	int	pid;
	int	x;
	int	y;

	if (pipe(p1) == -1)
		return (1);
	if (pipe(p2) == -1)
		return (2);
	pid = fork();
	if (pid == -1)
		return (3);
	if (pid == 0) // child proccess
	{
		close(p1[0]);
		close(p2[1]);
		if (read(p2[0], &x, sizeof(x)) == -1)
			return (4);
		printf ("Received x %d\n", x);
		x*= 4;
		if (write(p1[1], &x, sizeof(x)) == -1)
			return (4);
		printf("wrote x %d\n", x);
		close(p1[1]);
		close(p2[0]);
	}
	else // parent proccess
	{
		close(p2[0]); // not read from parent
		close(p1[1]); //not write from child
		y = 8;
		if (write(p2[1], &y, sizeof(y)) == -1)
			return 5;
		printf("wrote y %d\n", y);
		if (read(p1[0], &y, sizeof(y)) == -1)
			return 6;
		printf("Result y is %d\n", y);
		close(p2[1]);
		close(p1[0]);
	}
	return (0);
}