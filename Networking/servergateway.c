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

#define MYPORT 5999
#define BACKLOG 10
#define SERVER_IP "192.168.12.245"

int main()
{
  int sockfd, new_fd;
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
    /*
        if(!fork())
        {
          close(sockfd);
          exit(0);
        }
    */
    send(new_fd, "no number", 9, 0);
    close(new_fd);
    break;
  }
  
  close(sockfd);
  return 0;
}
