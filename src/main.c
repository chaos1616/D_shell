#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(void){
   unsigned char buffer[2048];
   char delim = ' ';
   char *delimptr = &delim;

   putchar('>');
   
   char *err = fgets(buffer, 2048, stdin);
   if(err == NULL){
      printf("Error reading file!\n");
      return 1;
   }
   
   for(char * token = 0; token != NULL; ){
      token = strtok(buffer, delimptr);
      if(strcmp(token, "ls") == 0){
         
      }
      
   return 0;
}

void runcommand(){
   pid_t child = fork();
   waitpid();


}
