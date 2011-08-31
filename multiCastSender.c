   #include <stdio.h>      /*  for fprintf() */
   #include <sys/socket.h> /*  for socket(), connect(), send(), and recv() */
   #include <arpa/inet.h>  /*  for sockaddr_in and inet_addr() */
   #include <stdlib.h>     /* for  atoi() */
   #include <string.h>     /* for  memset() */
   #include <unistd.h>     /* for  sleep() */

   #define MULTICASTIP "239.0.0.0"
   #define MULTICASTPORT 9999

   int main(int argc, char *argv[])
   {
   	int sockId;
        unsigned char multicastTTL;        
	struct sockaddr_in multicastAddr;
	unsigned int sendStringLen;
	char sendString[]="Multicast Data ..............";

     /* Create socket for sending/receiving datagrams */

     if ((sockId = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
     {
	perror("Socket");
	return -1;
     }

     /* Set TTL of multicast packet */

     if (setsockopt(sockId, IPPROTO_IP, IP_MULTICAST_TTL,(void *) &multicastTTL,sizeof(multicastTTL)) < 0)
     {
	perror("setsockopt");
	return -1;
     }


     /* Construct local address structure */

     memset(&multicastAddr, 0, sizeof(multicastAddr));       /* Zero out structure */

     multicastAddr.sin_family = AF_INET;                     /* Internet address family */

     multicastAddr.sin_addr.s_addr = inet_addr(MULTICASTIP);/* Multicast IP address */

     multicastAddr.sin_port = htons(MULTICASTPORT);             /* Multicast port */
                                              /* Find length of sendString */
     sendStringLen = strlen(sendString);

     for (;;) /* Run forever */
     {

          /* Multicast sendString in datagram to clients every 3 seconds */

          if (sendto(sockId, sendString, sendStringLen, 0, (struct sockaddr *)
                 &multicastAddr, sizeof(multicastAddr)) != sendStringLen)
	{
		perror("sendto");
		return -1;
	}
	else
	{
		printf("Data Sent ........\n");
	}
        sleep(3);

     }
     /* NOT REACHED */
 }

