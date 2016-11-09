#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>

#define CLE_MSQ 628
#define CLE_SHM 630
#define TAILLE 8


struct spectacle{
	long letype;
	char intitule[100];
	int nb_place;
	pid_t pid;
};

struct requete{
    int type_demande;
//    struct spectacle le_spectacle;
};

struct reponse{
	long letype; 
    int nb_place;
};

main()
{
	int msqid,shmid,l;
	struct spectacle *table_mem;
	struct spectacle le_spectacle;
	struct reponse la_reponse;
	struct requete la_requete;


	/* Cretation de la memoire partagee */
	
	shmid=shmget((key_t)CLE_SHM,TAILLE*sizeof(struct spectacle)-TAILLE*sizeof(long),0750 |IPC_CREAT | IPC_EXCL);
	
	if((table_mem=(spectacle *)shmat(shmid,NULL,0))==(char *)-1)
	{
		 perror("shmat");
		 exit(2);
	}

	/* Remplissage de la  table  en memoire avec les spectacles */

	strcpy(table_mem[0].intitule,"Marc Berthoumieux");
	table_mem[0].nb_place=50;
	
	strcpy(table_mem[1].intitule,"Ludovico Einaudi");
	table_mem[1].nb_place=50;
	
	strcpy(table_mem[2].intitule,"Nicki Bluhm and The Gramblers");
	table_mem[2].nb_place=50;

	strcpy(table_mem[3].intitule,"Les visites-Spectacles");
	table_mem[3].nb_place=50;

	strcpy(table_mem[4].intitule,"La Tour Eiffel, théâtre");
	table_mem[4].nb_place=50;

	strcpy(table_mem[5].intitule,"Hélène Ségara");
	table_mem[5].nb_place=50;
	
	strcpy(table_mem[6].intitule,"La double inconstance");
	table_mem[6].nb_place=50;

	strcpy(table_mem[7].intitule,"Gregory Porter");
	table_mem[7].nb_place=50;
	
	printf("ZEBRAAAAAAAAAAAAAAAA %d\n",table_mem[7].nb_place);

	/*   allocation  MSQ */
	if((msqid = msgget(CLE_MSQ, 0750 |IPC_CREAT | IPC_EXCL))<0)
	{
		perror("msgget");
		return -1;
	}

	while (1)
	{
	/* lecture d'une requête */
	if((l=msgrcv(msqid,&le_spectacle,sizeof(struct spectacle)-sizeof(long),7,0))<0)
	{
		perror("msgrcv");
		return -1;
	}else if(la_requete.type_demande==1){
		
	
   /* envoi de la réponse  */
	la_reponse.nb_place = 10;
	la_reponse.letype = le_spectacle.pid;
	   if(msgsnd(msqid,&la_reponse,sizeof(struct reponse)-sizeof(long),0)<0)
	{
		perror("msgsnd");
		exit(-1);
	}
	}
	}
	return 0;
}

