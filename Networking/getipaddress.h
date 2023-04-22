#include <stdio.h>
#include <stdlib.h>

char *getmyipaddr(void);

char *getmyipaddr(void)
{
  char *ch;
  FILE *fp;
  ch = malloc(15 * sizeof(char));
  system("/sbin/ifconfig>ipadd.txt");
  fp = fopen("ipadd.txt", "r");
  
  while (*ch != '\n')
  {
    fread(ch, sizeof(char), 1, fp);
  }
  
  while (*ch != ':')
  {
    fread(ch, sizeof(char), 1, fp);
  }
  
  fread(ch, sizeof(char), 15, fp);
  printf("%s is the ip address\n", ch);
  fclose(fp);
  return ch;
}
