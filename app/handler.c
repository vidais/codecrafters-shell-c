#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../lib/handler.h"

void command_handler(char *input){

    if (strncmp(input,"type",strlen("type"))){

        type(input+strlen("type "));
        return;

    } else if (strncmp(input,"exit",strlen("exit"))){

        int code = input + strlen("exit ");
        exit(code);

    } else if (strncmp(input, "echo",strlen("echo"))){
    
      printf("%s\n",input + strlen("echo "));
      return;
    
    } else {

        printf("%s: command not found\n", input);
        return;
    }
 
}

void type(char *input){

    char builtins[][16] = {"echo","type","cat","exit"};

    for(int i=0;i<sizeof(builtins);i++){    
        
        if(strncmp(input,builtins[i],sizeof(builtins[i]))){
            printf("%s is a shell builtin\n",input);
            return;
        }
    }
    invalid(input+5);
}

void invalid(char *input){
    fprintf(stderr,"%s: not found",input);
    return;
}