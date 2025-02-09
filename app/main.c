#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int main() {
  // Flush after every printf
  setbuf(stdout, NULL);
  // Wait for user input
  char input[100];

  while (true){
    
    printf("$ ");
    fgets(input, 100, stdin);
    
    input[strlen(input) - 1] = '\0';
    
    if(!strcmp(input, "exit 0")){

      exit(0);
    
    }else if (!strncmp(input, "echo",strlen("echo")))
    {
    
      printf("%s\n",input + strlen("echo "));
    
    } else {

      printf("%s: command not found\n", input);
    
    }
  }

  return 0;
}