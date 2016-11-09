/******************************************************************/
/* Processus serveur: crée la MSQ et additionne les deux nombres */
/*  reçus dans chaque message                                     */
/*****************************************************************/
//#include <stdio.h>
//#include <sys/types.h>
//#include <sys/ipc.h>
//#include <sys/msg.h>
//#include <stdlib.h>
#include <stdio.h> // Pour read() & write()
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>// Pour exit
#include <sys/ipc.h>
#include <sys/msg.h>

#define CLE 314

struct requete {
	long letype; 
	int nb1;
	int nb2;
	pid_t pid;
	};
struct reponse {
	long letype; 
	int res;
	};

main()
   {
   int msqid,l;
   struct requete la_requete;
   struct reponse la_reponse;

    /*   allocation  MSQ */
    if((msqid = msgget(CLE, 0660 |IPC_CREAT | IPC_EXCL))==-1)
    {
    perror("msgget");
    return -1;
    }
    while (1)
    {
   /* lecture d'une requête */
  if((l=msgrcv(msqid,&la_requete,sizeof(struct requete)-sizeof(long),3,0))==-1){
  perror("msgrcv");
  return -1;
  }

   /* envoi de la réponse  */
  la_reponse.res = la_requete.nb1 + la_requete.nb2;
  la_reponse.letype = la_requete.pid;

  if(msgsnd(msqid,&la_reponse,sizeof(struct reponse)-sizeof(long),0)==-1)
   {
   perror("msgsnd");
   exit(-1);
   }
   }
	return 0;
}


