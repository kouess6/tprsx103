#include <stdio.h> // Pour read() & write()
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>// Pour exit

main ()  {
		pid_t retour;
		char buff[256];
		char chaine1 []="hello, je suis le processus A , fils \n";
		char chaine2 []="hello, je suis le processus B , pere \n";
		
		int p1[2];
		int p2[2];
		pipe (p1);
		pipe (p2);
		retour=fork();
		if (retour == 0)
		{ 	
		close(p1[0]);
		close(p2[1]);
		write (p1[1],chaine1, strlen(chaine1));
		read (p2[0],buff,strlen(chaine2));
		printf("la chaine lue est %s\n", buff);								}else
		{ 
		close(p1[1]);
		close (p2[0]);
		write(p2[1],chaine2,strlen(chaine2));
		read (p1[0], buff, strlen(chaine1));
		printf("la chaine lue est %s\n", buff);		
		wait();
		}
}

