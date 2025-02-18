/* server.c */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
//#include <unistd. h.>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include "fa_collect.h"
//#define LOCAL_SERVER_PORT 2045
#define LOCAL_SERVER_PORT 32768
/*#define BUF 255
#define SAMPLES 2048*/
#define DATLEN 32

int main (int argc, char **argv) {
  char *hostname = NULL;
  struct hostent *hp;
  int s, rc, n ;
  unsigned int len;
  struct sockaddr_in cliAddr, servAddr;
  //char puffer[BUF];
  char puffer[MAX_LIB_THREADS][PAYLOAD_BUF_SIZE];
  time_t time1;
  char loctime[BUF];
  char *ptr;
  const int y = 1;
  int i=0,j=0;
  //int tmp_val ;
  int tmp_val[MAX_LIB_THREADS];
  /* fill mem */
  //memset(puffer, 0, BUF);
  memset(puffer, 0, sizeof (puffer));
  /* Socket erzeugen */
  s = socket (AF_INET, SOCK_DGRAM, 0);
  if (s < 0) {
     printf ("%s: Kann Socket nicht öffnen ...(%s)\n",
        argv[0], strerror(errno));
     exit (EXIT_FAILURE);
  }
  /* Lokalen Server Port bind(en) */
  servAddr.sin_family = AF_INET;
  //servAddr.sin_addr.s_addr = htonl (INADDR_ANY);
  // Get host info FQDN + IP in standard dot notation
  if (hostname) {
            if ( (hp = gethostbyname(hostname)) == NULL ) {
                printf("Server: Unknown host: %s", hostname);
            }
            memcpy((char*)&servAddr.sin_addr, hp->h_addr, hp->h_length);
        }
        else { // Use the host's own IP for server
            servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  }



  servAddr.sin_addr.s_addr = htonl (INADDR_ANY);
  servAddr.sin_port = htons (LOCAL_SERVER_PORT);
  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &y, sizeof(int));
  rc = bind ( s, (struct sockaddr *) &servAddr,
              sizeof (servAddr));
  if (rc < 0) {
     printf ("%s: Kann Portnummern %d nicht binden (%s)\n",
        argv[0], LOCAL_SERVER_PORT, strerror(errno));
     exit (EXIT_FAILURE);
  }
  printf ("%s: Wartet auf Daten am Port (UDP) %u\n",
     argv[0], LOCAL_SERVER_PORT);
  /* Serverschleife */
  while (1) {
    /* Puffer initialisieren */
    //memset (puffer, 0, BUF);
    memset (puffer, 0, sizeof(puffer));
    /* Nachrichten empfangen */
    len = sizeof (cliAddr);
    n = recvfrom ( s, puffer, sizeof(puffer), 0,
                   (struct sockaddr *) &cliAddr, &len );
    if (n < 0) {
       printf ("%s: Kann keine Daten empfangen ...\n",
          argv[0] );
       continue;
    }
    /* Zeitangaben präparieren */
    time(&time1);
    strncpy(loctime, ctime(&time1), BUF);
    ptr = strchr(loctime, '\n' );
    *ptr = '\0';
    /* Erhaltene Nachricht ausgeben */
    /*
    printf ("%s: Daten erhalten von %s:UDP%u : %s \n",
            loctime, inet_ntoa (cliAddr.sin_addr),
            ntohs (cliAddr.sin_port), puffer);
    */
    printf ("%s: Daten erhalten von %s:UDP%u : %d Bytes\n",
            loctime, inet_ntoa (cliAddr.sin_addr),
            ntohs (cliAddr.sin_port),n);

    for(i=0;i<n;i++)
              printf("idx:%d \t data:%d\n",i,puffer[0][i]);
    
    for (i = 0 ; i < (PAYLOAD_BUF_SIZE/4) ; i++) {
                //tmp_val = 0 ;
                tmp_val[0] = 0 ;
               	tmp_val[1] = 0 ;
               	tmp_val[2] = 0 ;
                
                for (j = 0 ; j < 4 ; j++) {
                        //tmp_val |= ((unsigned char)puffer[i*4+j]) << (j*8) ;
                        tmp_val[0] |= ((unsigned char)puffer[0][i*4+j]) << (j*8) ;
                        tmp_val[1] |= ((unsigned char)puffer[1][i*4+j]) << (j*8) ;
                        tmp_val[2] |= ((unsigned char)puffer[2][i*4+j]) << (j*8) ;
                        //printf("arch thread received data convert:\t %20d\t%20d\t%20d\n",tmp_val[0],tmp_val[1],tmp_val[2]);
                }
                
                
                //printf("--------------------\n");
                //fprintf(stdout, "0x%08X ", tmp_val) ;
                //fprintf(stdout, "data%d \t Libera 0 %11d \t Libera 1 %11d \tLibera 2 %11d \n", i,tmp_val[0],tmp_val[1],tmp_val[2]) ;
                //printf("arch thread received data:\t %20d\t%20d\t%20d\n",tmp_val[0],tmp_val[1],tmp_val[2]);
                printf("%d arch thread received data:\t %20d:%x\t%20d:%x\t%20d:%x\n",i,tmp_val[0],tmp_val[0],tmp_val[1],tmp_val[1],tmp_val[2],tmp_val[2]);
    }
    
    
  }
  return EXIT_SUCCESS;
}
