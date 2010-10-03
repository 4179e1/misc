#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
char buf1[]="abcdefghijklmnop";
char buf2[]="1234567890";
int main(void)
{    
       int fd;
       if((fd=open("filehole",O_RDWR|O_TRUNC|O_CREAT))<0)
              printf("create error\n");
       if(write(fd,buf1,strlen(buf1))!=16)
              printf("buf1 write error\n");
       if(lseek(fd,10000,SEEK_SET)==-1)
              printf("lseek error\n");
       if( write(fd,buf2,strlen(buf2))!=10)
           printf("buf2 write error\n");
       close(fd);
       return 0;
}
