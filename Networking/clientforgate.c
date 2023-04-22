# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <errno.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <netdb.h>
# include "gatewayinfo.h"

#define MYPORT 5003
#define MAXDATASIZE 100

int main(int argc, char *argv[])
{
  int sockfd, numbytes;
  char *adddata;
  adddata = malloc(15 * sizeof(char));
  char buf[MAXDATASIZE], input;
  struct hostent *he;
  struct sockaddr_in their_addr;
  
  if (argc != 2)
  {
    fprintf(stderr, "Usage: Client hostname\n");
    exit(1);
  }
  
  info data1;
  printf("%p is the address\n", &data1);
  printf("1. Quote for the day.\n2.Magic number.\n3.Lucky number.\n");
  he = gethostbyname(argv[1]);
  sockfd = socket(PF_INET, SOCK_STREAM, 0);
  their_addr.sin_family = AF_INET;
  their_addr.sin_port = htons(MYPORT);
  their_addr.sin_addr = *((struct in_addr *)he->h_addr);
  memset(&(their_addr.sin_zero), '\0', 8);
  connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr));
  numbytes = recv(sockfd, buf, MAXDATASIZE - 1, 0);
  buf[numbytes] = '\0';
  printf("Received:%s\n", buf);
  printf("Enter the input\n");
  scanf("%c", &input);
  send(sockfd, &input, sizeof(char), 0);
  recv(sockfd, (struct info1 *)&data1, sizeof(data1), 0);
  printf("received address is %p\n", &data1);
  printf("The port number to contact is %d\n", data1.portinfo);
  adddata = inet_ntoa(data1.ipaddresses);
  printf("%s is the ip to contact\n", adddata);
  close(sockfd);
  he = gethostbyname(adddata);
  sockfd = socket(PF_INET, SOCK_STREAM, 0);
  their_addr.sin_family = AF_INET;
  their_addr.sin_port = htons(data1.portinfo);
  their_addr.sin_addr = *((struct in_addr *)he->h_addr);
  memset(&(their_addr.sin_zero), '\0', 8);
  connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr));
  numbytes = recv(sockfd, buf, MAXDATASIZE - 1, 0);
  buf[numbytes] = '\0';
  printf("Received:%s\n", buf);
  close(sockfd);
  return 0;
}
