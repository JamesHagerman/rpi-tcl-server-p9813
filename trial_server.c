#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
//#include "str_echo.c"

int main()
  {
   int sockfd,connfd,childpid,clilen;
   struct sockaddr_in cliaddr,servaddr;

   sockfd = socket(AF_INET,SOCK_STREAM,0);
  
   bzero(&servaddr, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   servaddr.sin_port = htons(6060);
   bind(sockfd,(struct sockaddr*) &servaddr,sizeof(servaddr));
    
   listen(sockfd,5);

   while(1) {
      clilen=sizeof(cliaddr);
      connfd=accept(sockfd,(struct sockaddr*)&cliaddr,&clilen);
      printf("connection accepted\n");
      if((childpid=fork())==0) {
            close(sockfd);
            printf("child process\n");
            str_echo(connfd);
           // str_echo(connfd);
            exit(0);
      }
      printf("connection established\n");
      close(connfd);
      }
}