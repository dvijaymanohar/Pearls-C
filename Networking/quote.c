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
# include "getipaddress.h"

#define MYPORT 5999
#define BACKLOG 10

int main()
{
  int sockfd, new_fd, i;
  static int j = 1;
  char **quotes;
  char *SERVER_IP;
  SERVER_IP = malloc(15 * sizeof(char));
  SERVER_IP = getmyipaddr();
  quotes = malloc(20 * sizeof(int));
  
  for (i = 0; i < 20; i++)
  {
    *quotes = malloc(80 * sizeof(char));
  }
  
  quotes[1] = "Eat good think better";
  quotes[2] = "Live the best";
  quotes[3] = "Life id yours live it to the fullest";
  quotes[4] = "ok ok ok ";
  quotes[5] = "This the number 5";
  quotes[6] = "This the number 6";
  quotes[7] = "This the number 7";
  quotes[8] = "This the number 8";
  quotes[9] = "This the number 9";
  quotes[10] = "This the number 10";
  struct sockaddr_in my_addr;
  struct sockaddr_in their_addr;
  socklen_t sin_size;
  sockfd = socket(PF_INET, SOCK_STREAM, 0);
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(MYPORT);
  my_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
  memset(&(my_addr.sin_zero), '\0', 8);
  bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr));
  listen(sockfd, BACKLOG);
  
  while (1)
  {
    sin_size = sizeof(struct sockaddr_in);
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
    printf("Got connection from : %s\n", inet_ntoa(their_addr.sin_addr));
    
    if (!fork())
    {
      close(new_fd);
      exit(0);
    }
    
    send(new_fd, quotes[j], 40, 0);
    close(new_fd);
    j++;
    
    if (j >= 9)
    {
      j = 1;
    }
  }
  
  close(sockfd);
  return 0;
}
