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
	msqid=msgget(cle,0);
//	rep.type=6;
	//msgrcv(msqid,&req,sizeof(struct requete),5,0);
	msgrcv(msqid,&req,sizeof(struct requete),5,0);
	printf("Message recu: %d %d \n",req.nb1,req.nb2);
//	rep.res=req.nb1+req.nb2;
//	msgsnd(msqid,&rep,sizeof(struct reponse),0);
//	msgctl (msqid, IPC_RMID, NULL);
}
