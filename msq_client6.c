#include <stdio.h> // Pour read() & write()
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>// Pour exit
#include <sys/ipc.h>
#include <sys/msg.h>

#define cle 50

struct requete{
	long type;
	int nb1;
	int nb2;
};
struct reponse{
    long type;
    int res;
};

struct requete req;
//struct reponse rep;

int main(){
	int msqid;
	msqid=msgget(cle, IPC_CREAT | IPC_EXCL | 0666);
	req.type=5;
	printf("Saisir les deux nombres \n");
	scanf("%d %d",&req.nb1,&req.nb2);
	msgsnd(msqid,&req,sizeof(struct requete),0);
   // if(msgrcv(msqid,&rep,sizeof(struct requete),6,0))
//	printf("Le resultat de l'addition est : %d \n",rep.res);
}

