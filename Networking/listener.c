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

# define PORT 4950
# define MAXBUFLEN 100
# define MYIP "192.168.12.223"
int main()
{
  int sockfd;
  struct hostent *he;
  struct sockaddr_in my_addr;
  struct sockaddr_in their_addr;
  socklen_t addr_len;
  int numbytes;
  char buf[MAXBUFLEN];
  sockfd = socket(PF_INET, SOCK_DGRAM, 0);
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(PORT);
  my_addr.sin_addr.s_addr = inet_addr(MYIP);
  their_addr.sin_family = AF_INET;
  their_addr.sin_port = htons(PORT);
  their_addr.sin_addr = *((struct in_addr *)he->h_addr);
  memset(&(my_addr.sin_zero), '\0', 8);
  bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr));
  addr_len = sizeof(struct sockaddr);
  numbytes = recvfrom(sockfd, buf, MAXBUFLEN - 1, 0, (struct sockaddr *)&their_addr, &addr_len);
  printf("got packet from %s\n", inet_ntoa(their_addr.sin_addr));
  printf("Packet is %d bytes long", numbytes);
  buf[numbytes] = '\0';
  printf("Packet contains \" %s \"\n", buf);
  sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&their_addr, sizeof(struct sockaddr));
  printf("HI");
  close(sockfd);
  return 0;
}
