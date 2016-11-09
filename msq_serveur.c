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
msqid=msgget(cle, IPC_CREAT | IPC_EXCL | 0666);
msg_srv.mtype=5;
strcpy(msg_srv.mtext,"Message du serveur");
msgsnd(msqid,&msg_srv,strlen(msg_srv.mtext),0);
}
