#include <stdio.h>
#include <stdbool.h>

int main() {
  // Flush after every printf
  setbuf(stdout, NULL);


  // Wait for user input
  char input[100];

  while (true){
    
    printf("$ ");
    fgets(input, 100, stdin);
    
    if(strcmp(input, "exit 0")){
      return 0;
    } else {
      input[strlen(input) - 1] = '\0';
      printf("%s: command not found\n", input);
    }
  }

  return 0;
}