/******************************************************************/
/* Processus client: envoi deux nombres à additionner            */
/******************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

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
	int msqid, l, nb1, nb2;	
	struct requete la_requete;
	struct reponse la_reponse;

	/* récupération du msqid */
	 if ((msqid = msgget(CLE,0)) <0)
		    {
				     perror("msgget");
					      exit(-1);
						     }

	 /* préparation de la requête et envoi */
	 printf ("Donnez moi deux nombres à additionner:");
	 scanf ("%d %d", &nb1, &nb2);

	 la_requete.letype = 1;
	 la_requete.nb1 = nb1;
	 la_requete.nb2 = nb2;
     la_requete.pid = getpid(); 


	  /* envoi de la requete */
	   if(msgsnd(msqid,&la_requete,sizeof(struct requete)-sizeof(long),0)==-1)
	   {
		     perror("msgsnd");
			   exit(-1);
	   }
	   /* réception de la réponse */
	   if(msgrcv(msqid,&la_reponse,sizeof(struct reponse)-sizeof(long),getpid(),0)==-1)
		     {
				     perror("msgrcv");
					     exit(-1);
						   }


	   printf ("le resultat reçu est: %d\n", la_reponse.res);
	   exit;
}



