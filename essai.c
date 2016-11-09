#include <stdio.h>
#include <unistd.h>      // Pour le PID
#include <sys/types.h>   // Pour le type PID
#include "errno.h"       // Pour errno
main()
{
	int pid;
	pid = fork();
	if (pid == 0)
	{
		printf ("je suis le fils\n");
		execl("/bin/ls","ls","-l",NULL);
		//printf ("Mon pid est %d \n",getpid());
		//printf ("Le pid de mon pere est %d \n", getppid());
	}
	else
	{
		printf("je suis le père\n");
		printf ("Mon pid est %d \n", getpid());
		printf ("Le pid de mon fils %d \n",pid);
		wait();
	}
}
