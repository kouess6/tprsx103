#include <stdio.h> // Pour read() & write()
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>// Pour exit
#include <sys/ipc.h>
#include <sys/msg.h>

#define cle 17

struct msgbuf{
	    long mtype;
	    char mtext[20];
};
struct msgbuf msg_srv;

int main(){
	int msqid;
	printf("ALLO");
	msqid=msgget(cle,0);
	msgrcv(msqid,&msg_srv,20,5,0);
	printf("Message recu: %s \n",&msg_srv.mtext);
	msgctl(msqid,IPC_RMID,NULL);
}
