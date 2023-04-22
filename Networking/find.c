# include <stdio.h>
# include "getipaddress.h"

int main()
{
  char *ip;
  ip = malloc(16 * sizeof(char));
  ip = getmyipaddr();
  printf("My ip address is %s", *ip);
  return 0;
}
