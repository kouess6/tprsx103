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

struct spectacle {
	char intitule[100];
	int nb_place;
};

struct requete{
	long letype;
	int type_demande;
	char intitule[100];
	pid_t pid;
	//    struct spectacle le_spectacle;
};

struct reponse{
	long letype;
	int nb_place;
};

int main(){

	int msqid,shmid,l;
	//char spect_intitule[100];
	struct spectacle le_spectacle;
	struct requete la_requete;
	struct reponse la_reponse;
	struct spectacle *table_mem,*p;

	/* Cretation de la memoire partagee */

	shmid=shmget((key_t)CLE_SHM,TAILLE*sizeof(struct spectacle)-TAILLE*sizeof(long),0750 |IPC_CREAT | IPC_EXCL);
	
	if(((table_mem=shmat(shmid,NULL,0))==(struct spectacle*)-1)){
		perror("shmat");
		exit(2);
	}
printf("OKI 1\n");
	 /* Remplissage de la  table  en memoire avec les spectacles */

	strcpy(table_mem->intitule,"Marc Berthoumieux");
	table_mem->nb_place=50;

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
	table_mem[7].nb_place=150; 

	//strcpy(le_spectacle.intitule,"Bonjour GAD");
	//le_spectacle.nb_place=50;
	//la_requete.le_spectacle.nb_place=60;
	//printf("%d \n",le_spectacle.nb_place);
	printf("%d \n",(table_mem+8)->nb_place);
	printf("%s \n",(table_mem+8)->intitule);
	//printf("%s \n",le_spectacle.intitule);

	printf("OKI 2\n");

	/*   allocation  MSQ */
    if((msqid = msgget(CLE_MSQ, 0750 |IPC_CREAT | IPC_EXCL))<0)
	{
		perror("msgget");
		return -1;
	}
	while (1)
	{
		/* lecture d'une requête */
		if((l=msgrcv(msqid,&la_requete,sizeof(struct requete)-sizeof(long),1,0))<0)
		{
			perror("msgrcv");
			return -1;
		}else if(la_requete.type_demande==0){
		/* envoi de la réponse  */
		for(p =&table_mem[0];p<&table_mem[7];p++){
				if(strcmp(p->intitule,le_spectacle.intitule)==0){
				la_reponse.nb_place = p->nb_place;
				la_reponse.letype = la_requete.pid;
				printf("OK3\n");
				break;
		}
				
					if(msgsnd(msqid,&la_reponse,sizeof(struct reponse)-sizeof(long),0)<0)
					{
						perror("msgsnd");
						exit(-1);
					}
				}
			//}
		}
	}
	printf("OK4\n");
	    return 0;
}



														
