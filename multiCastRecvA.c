   #include  <stdio.h>       /* for printf() and fprintf() */
   #include  <sys/socket.h>  /* for socket(), connect(), sendto(), and recvfrom() */
   #include  <arpa/inet.h>   /* for sockaddr_in and inet_addr() */
   #include  <stdlib.h>      /* for atoi() */
   #include  <string.h>      /* for memset() */
   #include  <unistd.h>      /* for close() */

   #define MAXRECVSTRING 255    /* Longest string to receive */
   #define MULTICASTIP "239.0.0.0"
   #define MULTICASTPORT 9999

   int main(int argc, char *argv[])
   {
   	int sockId;                           /*  Socket */

       struct sockaddr_in multicastAddr;   /*  Multicast Address */

       char recvString[MAXRECVSTRING];   /*  Buffer for received string */

       int recvStringLen;                  /*  Length of received string */

       struct ip_mreq multicastRequest;    /*  Multicast address join structure */

      /* Create a best-effort datagram socket using UDP */

	if ((sockId = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	{
		perror("socket");
		return -1;
	}


   /* Construct bind structure */

   /* Zero out structure */
   memset(&multicastAddr, 0, sizeof(multicastAddr));
   multicastAddr.sin_family = AF_INET;
   multicastAddr.sin_addr.s_addr = htonl(INADDR_ANY) ; /*   Any incoming interface */                                                           
   multicastAddr.sin_port = htons(MULTICASTPORT) ; /* Multicast port */


   /* Bind to the multicast port */
   if (bind(sockId, (struct sockaddr *) &multicastAddr, sizeof(multicastAddr)) < 0)
   {
	perror("bind");
	return -1;
   }

   /* Specify the multicast group */

   multicastRequest.imr_multiaddr.s_addr = inet_addr(MULTICASTIP);

   /* Accept multicast from any interface */

   multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY);

   /* Join the multicast group */

   if (setsockopt(sockId, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *) &multicastRequest,sizeof(multicastRequest)) < 0)
   {
	perror("setsockopt");
	return -1;
   }

   /* Receive a single datagram from the server */
   for(;;)
   {
	if ((recvStringLen = recvfrom(sockId, recvString, MAXRECVSTRING, 0, NULL, 0)) < 0)
	{
		perror("recvfrom");
		return -1;
	}
	recvString[recvStringLen] = '\0';
        printf("Received' %s\n", recvString) ;
  }

   close(sockId) ;
}


