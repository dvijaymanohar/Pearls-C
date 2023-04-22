#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct info1
{
  unsigned short portinfo;
  struct in_addr ipaddresses;
} info;
