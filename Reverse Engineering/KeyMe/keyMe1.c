/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * GitHub:RafaelEstevamReis wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.   Poul-Henning Kamp
 * ----------------------------------------------------------------------------
 */
 
 /*
  * ------------------------------
  *  DO NOT LOOK AT THE CODE BELOW
  *
  *  You must analyse the compiled
  *  version of it.
  * ------------------------------
  */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool checkChars(char* key){
    int len =  strlen(key);
    for(int i = 0; i < len;i++){
        if(key[i] < '0' || key[i] > '9') return false;
    }
    return true;
}
bool validate(char* key){
    int len =  strlen(key);
    int sum = 0;
    for(int i = 0; i < len -1;i++){
        sum += key[i]-'0';
    }
    sum = sum % 10;
    if(('0' + sum) == key[len-1]) return true;
    return false;
}

int main(int argc, char *argv[]){
    // argc == 0 ?
    // argc == 1 Only path
    // argc == 2 Okay
    // argc > 2 Error
    if(argc < 2){
        printf("Missing KEY\n");
        exit(-1);
    }
    if(argc > 2){
        printf("Invalid args\n");
        exit(-1);
    }

    if(strlen(argv[1]) != 16){
         printf("Invalid Key EC249\n");
        exit(-1);
    }
    if(!checkChars(argv[1])){
         printf("Invalid Key EC758\n");
        exit(-1);
    }
    if(!validate(argv[1])){
         printf("Invalid Key EC209\n");
        exit(-1);
    }

    printf("You have registered your application\n");
    return 0;
}