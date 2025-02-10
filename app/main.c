#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// returns a string with a \n before the \0 and should be freed
char *read_line() {
  size_t size = 1; // getline automatically "realloc"s more space
  char *buffer = malloc(sizeof(char) * size);
  size_t status = getline(&buffer, &size, stdin);
  if (status == -1) {
    fprintf(stderr, "[ERROR] cannot read input from stding\n");
  }
  for (size_t i = 0; i < size; i++) {
    if (buffer[i] == '\n' || buffer[i] == '\r') {
      buffer[i] = '\0';
      break;
    }
  }
  return buffer;
}
// Commands
/*
struct Command{
  enum CommandType cmd;
  char* raw_command;
  int (*validate)(char* str);
  ssize_t (*execute)(char* str);
};
struct Command** init_commands(size_t* count){
  struct Command* exitc = malloc(sizeof(struct Command));
  exitc->cmd = _exit;
  exitc->validate = validate_exit;
  exitc->execute = execute_exit;
  struct Command **commands = malloc(sizeof(struct Command*) * 8);
  commands[0] = exitc;
  *count = 1;
  return commands;
}
ssize_t execute_exit(char* str){
  printf("Executing exit\n");
  return 0;
}
int validate_exit(char* str){
  return strncmp("exit", str, 4) == 0;
}
enum CommandType{
  _invalid, _exit,
};
enum CommandType validate(char* input){
  if(validate_exit(input)) return _exit;
  else return _invalid;
}
*/
void handle_input(char *input) {
  if (strncmp("exit", input, 4) == 0) {
    char *arguments = input + 4;
    errno = 0;
    char *endptr;
    int exit_status =
        strtol(arguments, &endptr, 10); // +4 to remove the "exit" word
    if (errno != 0) {
      perror("strtol");
      exit(EXIT_FAILURE);
    }
    if (endptr == arguments) {
      fprintf(stderr, "No exit status was found\n");
      return;
    }
    exit(exit_status);
  } else if (strncmp("echo", input, 4) == 0) {
    printf("%s\n", input + 5);
  } else if (strncmp("type", input, 4) == 0) {
    char builtins[][16] = {"echo", "type", "exit", "cat"};
    char *arguments = input + 5;
    for (size_t i = 0; i < sizeof(builtins) / 16; i++) {
      if (strcmp(builtins[i], arguments) == 0) {
        printf("%s is a shell builtin\n", arguments);
        return;
      }
    }
    printf("%s not found\n", arguments);
  } else {
    fprintf(stderr, "%s: command not found\n", input);
  }
}
int main() {
  while (1) {
    printf("$ ");
    fflush(stdout);
    char *input = read_line();
    handle_input(input);
    free(input);
  }
  return 0;
}