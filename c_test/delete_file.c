#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void)
{
  char fname[80];

  printf("Enter name of file to delete: ");
  gets(fname);
 
  printf("Are you sure? (Y/N) ");
 
  if(toupper(getchar())=='Y') 
      remove(fname);

  return 0;
}

