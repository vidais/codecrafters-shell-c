#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../lib/handler.h"

int main() {
  // Flush after every printf
  setbuf(stdout, NULL);
  // Wait for user input
  char input[100];

  while (true){
    
    printf("$ ");
    fgets(input, 100, stdin);
    
    input[strlen(input) - 1] = '\0';

    command_handler(input);

    }

  return 0;
}