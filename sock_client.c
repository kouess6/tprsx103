#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> 
#include <netdb.h> 

struct sockaddr_in {
	uint8_t         sin_len;       /* longueur totale      */
	sa_family_t     sin_family;    /* famille : AF_INET     */
	in_port_t       sin_port;      /* le numéro de port    */
	struct in_addr  sin_addr;
	unsigned char   sin_zero[8];   /* Bourage */
};

struct sockaddr {
	unsigned char   sa_len;         /* longueur totale 		*/
	sa_family_t     sa_family;      /* famille d'adresse 	*/
	char            sa_data[14];    /* valeur de l'adresse	*/
};
