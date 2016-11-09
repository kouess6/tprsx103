/******************************************************************/
/* Processus client: envoi deux nombres à additionner            */
/******************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>

#define CLE_MSQ 628
#define CLE_SHM 630
#define TAILLE 8


struct spectacle{ 
	char intitule[100];
	int nb_place;
    };

struct requete{
	long letype;
	int type_demande;
	char intitule[100];
	pid_t pid;
	//struct spectacle *le_spectacle;
};

struct reponse {
	long letype; 
	int nb_place;
	};

int main()
{
	int msqid, demande;
	char spect_intitule[100];
	//struct spectacle le_spectacle;
	struct requete la_requete;
	struct reponse la_reponse;
//	struct spectacle *table_mem;
	
	/* récupération du msqid */
	if ((msqid = msgget(CLE_MSQ,0)) <0)
	{
		perror("msgget");
		exit(-1);
	}
	 
	/* préparation de la requête et envoi */
	 la_requete.letype = 1;
	 printf("Saisir l'intitulé du spectacle!");
	 scanf("%s \n",spect_intitule);
	 
	 strcpy(la_requete.intitule,spect_intitule);
	 
	 printf("Saisir le type de requete! \nPour Consultation:0. pour  Reservation: 1 \n");
	 scanf("%d: \n",&demande);
     la_requete.type_demande=demande;
	 la_requete.pid = getpid(); 

	  /* envoi de la requete */
	   if(msgsnd(msqid,&la_requete,sizeof(struct requete)-sizeof(long),0)==-1)
	   {
		     perror("msgsnd");
			   exit(-1);
	   }
	   else {
	   printf("OK\n");
	   
	   /* réception de la réponse */
	   if(msgrcv(msqid,&la_reponse,sizeof(struct reponse)-sizeof(long),getpid(),0)==-1)
	   {
		   perror("msgrcv");
		   exit(-1);
	   }else{
	   	  printf("OK2");
		  printf ("le resultat reçu est: %d\n", la_reponse.nb_place);
	   }
	   }
	   exit;
}



