#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int pip[2];
void lecteurferme();
main()
{
	int nb_ecrit;
	int pid;
	signal(SIGPIPE,lecteurferme);
	/* ouverture d'un pipe */
	if(pipe(pip))
	{ perror("pipe");
		exit(-1);}
	pid = fork();
	if (pid == 0)
	{
		close(pip[0]);
		close(pip[1]);
		printf("Je suis le fils\n");
		exit(-1);
	}
	else
	{
		close(pip[0]);
		for(;;){
			if ((nb_ecrit = write(pip[1], "ABC", 3)) == -1)
			{
				perror ("pb write");
				exit(-1);
			}
			else printf ("retour du write : %d\n", nb_ecrit);
		}
	}
}
void lecteurferme(){
	printf("Pas de lecteur sur le tube \n");
}
