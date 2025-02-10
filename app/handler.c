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

<<<<<<< HEAD
    } else if (strncmp(input, "echo",strlen("echo"))){
=======
    } else if (!strncmp(input, "echo",strlen("echo"))){
>>>>>>> d43ccf3e1eda217dd3d2fb5fae91aff9b3b4e00f
    
      printf("%s\n",input + strlen("echo "));
      return;
    
    } else {

        printf("%s: command not found\n", input);
        return;
    }
 
}

void type(char *input){

    char builtins[][16] = {"echo","type","cat","exit"};

<<<<<<< HEAD
    for(int i=0;i<sizeof(builtins);i++){    
=======
    for(int i=0;i<4;i++){    
>>>>>>> d43ccf3e1eda217dd3d2fb5fae91aff9b3b4e00f
        
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