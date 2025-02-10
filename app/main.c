#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int is_executable(const char *path){ return access(path,X_OK)==0; }

char *find_in_path(const char *command){
  char *path_env = getenv("PATH");
  if (path_env == NULL){
    return NULL; 
  }

  char *path_copy = strdup(path_env);
  char *dir = strtok(path_copy,":");
  static char full_path[1024];

  while (dir != NULL) {
    snprintf(full_path,sizeof(full_path),"/%s/%s",dir,command);
    if (is_executable(full_path)){
      free(path_copy);
      return full_path;
    }
    dir = strtok(NULL,":");
  }

  free(path_copy);
  return NULL;
}

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
    char builtins[][16] = {"ls","echo", "type", "exit", "cat"};
    char *arguments = input + 5;
    for (size_t i = 0; i < sizeof(builtins) / 16; i++) {
      if (strcmp(builtins[i], arguments) == 0) {
        printf("%s is a shell builtin\n", arguments);
        return;
      }
    }
    printf("%s not found\n", arguments);
    char *path = find_in_path(command);
    if (path){
      printf("%s is %s\n",command,path);
    } else printf("%s: not found\n", command);

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