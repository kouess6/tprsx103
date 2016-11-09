all : bonjour essai tube handler_exo5 msq_serveur msq_client msq_serveur6 msq_client6 tp6_serveur tp6_client msqs msqc projet_serveur projet_client 

bonjour : bonjour.c
	gcc bonjour.c -o bonjour

essai : essai.c
	gcc essai.c -o essai

tube : tube.c
	gcc tube.c -o tube

handler_exo5 : handler_exo5.c
	gcc handler_exo5.c -o handler_exo5

msq_serveur : msq_serveur.c
	gcc msq_serveur.c -o msq_serveur

msq_client : msq_client.c
	gcc msq_client.c -o msq_client

msq_serveur6 : msq_serveur6.c
	gcc msq_serveur6.c -o msq_serveur6

msq_client6 : msq_client6.c
	gcc msq_client6.c -o msq_client6

tp6_serveur : tp6_serveur.c
	gcc tp6_serveur.c -o tp6_serveur

tp6_client : tp6_client.c
	gcc tp6_client.c -o tp6_client
msqs : msqs.c
	gcc msqs.c -o msqs

msqc : msqc.c
	gcc msqc.c -o msqc

projet_serveur : projet_serveur.c
	gcc -g -Wall projet_serveur.c -o projet_serveur

projet_client : projet_client.c
	gcc -g -Wall projet_client.c -o projet_client
clean :
	rm -f bonjour
	rm -f essai
	rm -f tube
	rm -f handler_exo5
	rm -f msq_serveur
	rm -f msq_client
	rm -f msq_serveur6
	rm -f msq_client6
	rm -f tp6_serveur
	rm -f tp6_client
	rm -f msqs
	rm -f msqc
	rm -f projet_serveur
	rm -f projet_client
