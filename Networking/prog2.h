# include <stdio.h>
# include <stdlib.h>

int main()
{
  char *bypass;
  bypass = malloc(80 * sizeof(char));
  scanf("%s", bypass);
  return 0;
}
