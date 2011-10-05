#include <pcap.h>
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h> 

#define ETHER_ADDR_LEN 6
#define SIZE_ETHERNET 14

#define IP_HL(ip)               (((ip)->ip_vhl) & 0x0f)  

/* Ethernet header */  
struct sniff_ethernet {  
         u_char  ether_dhost[ETHER_ADDR_LEN];    /* destination host address */  
         u_char  ether_shost[ETHER_ADDR_LEN];    /* source host address */  
         u_short ether_type;                     /* IP? ARP? RARP? etc */  
};

/* IP header */  
struct sniff_ip {  
         u_char  ip_vhl;                 /* version << 4 | header length >> 2 */  
         u_char  ip_tos;                 /* type of service */  
         u_short ip_len;                 /* total length */  
         u_short ip_id;                  /* identification */  
         u_short ip_off;                 /* fragment offset field */  
         u_char  ip_ttl;                 /* time to live */  
         u_char  ip_p;                   /* protocol */  
         u_short ip_sum;                 /* checksum */  
         struct  in_addr ip_src,ip_dst;  /* source and dest address */  
}; 

struct sniff_udp
{
	u_short src_port;	/* source port num */
	u_short dest_port; 	/* dest port num */
	u_short total_len;	/* len - data+checksum */
	u_short checksum; 	/* checksum */
};

void  print_hex_ascii_line(const u_char *payload, int len, int offset)  
{  
   
  int i;  
  int gap;  
  const u_char *ch;  
   
  /* offset */  
  printf("%05d   ", offset);  
    
  /* hex */  
  ch = payload;  
  for(i = 0; i < len; i++) {  
   printf("%02x ", *ch);  
   ch++;  
   /* print extra space after 8th byte for visual aid */  
   if (i == 7)  
    printf(" ");  
  }  
  /* print space to handle line less than 8 bytes */  
  if (len < 8)  
   printf(" ");  
    
  /* fill hex gap with spaces if not full line */  
  if (len < 16) {  
   gap = 16 - len;  
   for (i = 0; i < gap; i++) {  
    printf("   ");  
   }  
  }  
  printf("   ");  
    
  /* ascii (if printable) */  
  ch = payload;  
  for(i = 0; i < len; i++) {  
   if (isprint(*ch))  
    printf("%c", *ch);  
   else  
    printf(".");  
   ch++;  
  }  
   
  printf("\n");  
   
 return;  
} 

void print_payload(const u_char* payload, int len)
{
    int offset = 0;
    int len_rem = len;
    if(len <= 0)
    {
	printf("Payload is empty \n");
	return;
    }
    /* print 16 bytes at shot */
    if(len < 16)
    {
        print_hex_ascii_line(payload, len, 0);
        return;
    }

    while(1)
    {
        print_hex_ascii_line(payload,16,offset); // print 16 bytes
        offset = offset + 16;
        payload = payload + 16;
        
        len_rem = len_rem -16;
        
        printf("offset %d len_rem %d \n",offset,len_rem);
        /* break if last line */
        if(len_rem < 16)
        {
		print_hex_ascii_line(payload,len_rem,offset);
		printf("In if \n");
		break;
        }
    }
}
void handle_udp_packet(const u_char* packet)
{
	const struct sniff_udp *udp;
        int len;
	udp = (struct sniff_udp *)(packet);
	printf("UDP HEADER \n");
	printf("src port %d\n",ntohs(udp->src_port));
	printf("dest port %d\n",ntohs(udp->dest_port));
        len = ntohs(udp->total_len);
        printf("len: %d\n",len);
        print_payload((packet+8),len-8); //UDP header 8 bytes
}
void got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{
	int i;
	const struct sniff_ethernet *ether;
	const struct sniff_ip *ip;
	int size_ip;
	ether = (struct sniff_ethernet *)packet;
	ip = (struct sniff_ip *)(packet + SIZE_ETHERNET);
#if 0	
	for(i=0;i<6;i++)
	{
		printf("0x%x\n",ether->ether_shost[i]);
	}
#endif
	size_ip = IP_HL(ip)*4;  
	if (size_ip < 20) 
	{  
		printf("   * Invalid IP header length: %u bytes\n", size_ip);  
	   	return;  
	}
	/* print source and destination IP addresses */  
	printf("       From: %s\n", inet_ntoa(ip->ip_src));  
	printf("         To: %s\n", inet_ntoa(ip->ip_dst));
	
	switch(ip->ip_p)
	{
		case IPPROTO_TCP:
		printf("Received TCP Packet \n");
		break;
		case IPPROTO_UDP:
		handle_udp_packet((packet+SIZE_ETHERNET+size_ip));
		break;
		default:
		printf("Invalid Packet !!! \n");
		break;
	}
}
int main()
{
	 pcap_t *handle;		/* Session handle */
	 char dev[] = "eth0";		/* Device to sniff on */
	 char errbuf[PCAP_ERRBUF_SIZE];	/* Error string */
	 struct bpf_program fp;		/* The compiled filter expression */
	 char filter_exp[] = "port 9999";	/* The filter expression */
	 bpf_u_int32 mask;		/* The netmask of our sniffing device */
	 bpf_u_int32 net;		/* The IP of our sniffing device */

	 if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1) {
		 fprintf(stderr, "Can't get netmask for device %s\n", dev);
		 net = 0;
		 mask = 0;
	 }
	 handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
	 if (handle == NULL) {
		 fprintf(stderr, "Couldn't open device %s: %s\n", dev, errbuf);
		 return(2);
	 }
	 if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1) {
		 fprintf(stderr, "Couldn't parse filter %s: %s\n", filter_exp, pcap_geterr(handle));
		 return(2);
	 }
	 if (pcap_setfilter(handle, &fp) == -1) {
		 fprintf(stderr, "Couldn't install filter %s: %s\n", filter_exp, pcap_geterr(handle));
		 return(2);
	 }
	/* Receive the packets */
	while(1)
	{
		pcap_loop(handle,1,got_packet,NULL);
	}
	pcap_close(handle);
}
