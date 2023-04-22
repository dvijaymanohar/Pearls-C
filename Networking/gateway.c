#include <stdio.h>
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
# include "getipaddress.h"

#define MYPORT 5003
#define BACKLOG 10

int main()
{
  int sockfd, new_fd;
  struct sockaddr_in my_addr;
  struct sockaddr_in their_addr;
  char buf1[2];
  char *SERVER_IP;
  SERVER_IP = malloc(15 * sizeof(char));
  SERVER_IP = getmyipaddr();
  printf("%s is the ip addr\n", SERVER_IP);
  struct hostent *he;
  socklen_t sin_size;
  sockfd = socket(PF_INET, SOCK_STREAM, 0);
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(MYPORT);
  my_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
  memset(&(my_addr.sin_zero), '\0', 8);
  bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr));
  info mydata1, mydata2, mydata3;
  printf("%d is the size of the structure", sizeof(mydata1));
  mydata1.portinfo = 5999;
  mydata2.portinfo = 5998;
  mydata3.portinfo = 5997;
  inet_aton(SERVER_IP, &mydata1.ipaddresses.s_addr);
  inet_aton(SERVER_IP, &mydata2.ipaddresses.s_addr);
  inet_aton(SERVER_IP, &mydata3.ipaddresses.s_addr);
  printf("%x is the adderss\n", mydata1.ipaddresses.s_addr);
  listen(sockfd, BACKLOG);
  
  while (1)
  {
    sin_size = sizeof(struct sockaddr_in);
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
    printf("Got connection from : %s\n", inet_ntoa(their_addr.sin_addr));
    
    if (!fork())
    {
      close(sockfd);
      exit(0);
    }
    
    send(new_fd, "Give input:", 12, 0);
    recv(new_fd, &buf1, sizeof(char), 0);
    printf("Got the following from the client %c\n", *buf1);
    
    switch (*buf1)
    {
      case '1':
        {
          send(new_fd, &mydata1, sizeof(mydata1), 0);
          printf("sent address is %p\n", &mydata1);
          break;
        }
        
      case '2':
        {
          send(new_fd, &mydata2, sizeof(mydata2), 0);
          printf("sent address is %p\n", &mydata2);
          break;
        }
        
      case '3':
        {
          send(new_fd, &mydata3, sizeof(mydata3), 0);
          printf("sent address is %p\n", &mydata3);
          break;
        }
        
      default:
        {
          printf("Sorry service not available");
          break;
        }
    }
    
    close(new_fd);
  }
  
  close(sockfd);
  return 0;
}
