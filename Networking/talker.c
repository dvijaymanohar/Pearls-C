# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>

# define SERVERPORT 4950
# define MYIP "192.168.12.223"
# define MAXBUFLEN 100

int main(int argc, char *argv[])
{
  int sockfd;
  struct sockaddr_in their_addr;
  struct sockaddr_in my_addr;
  struct hostent *he;
  socklen_t addr_len;
  int numbytes;
  char buf[MAXBUFLEN];
  
  if (argc != 3)
  {
    fprintf(stderr, "Usage: Talker hostname message\n");
    exit(1);
  }
  
  he = gethostbyname(argv[1]);
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(SERVERPORT);
  my_addr.sin_addr.s_addr = inet_addr(MYIP);
  their_addr.sin_family = AF_INET;
  their_addr.sin_port = htons(SERVERPORT);
  their_addr.sin_addr = *((struct in_addr *)he->h_addr);
  memset(&(their_addr.sin_zero), '\0', 8);
  numbytes = sendto(sockfd, argv[2], strlen(argv[2]), 0, (struct sockaddr *)&their_addr, sizeof(struct sockaddr));
  printf("Sent %d bytes to %s\n", numbytes, inet_ntoa(their_addr.sin_addr));
  //  recvfrom(sockfd, buf, MAXBUFLEN-1, 0, (struct sockaddr *)&their_addr, &addr_len);
  close(sockfd);
  return 0;
}
