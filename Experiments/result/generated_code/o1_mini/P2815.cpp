#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char input[40];
    scanf("%39s", input);
    char *groups[8];
    int idx = 0;
    char *token = strtok(input, ":");
    while(token && idx <8){
        groups[idx++] = token;
        token = strtok(NULL, ":");
    }
    // Remove leading zeros
    char *compressed[8];
    for(int i=0;i<8;i++){
        int start=0;
        while(groups[i][start] =='0' && start <3) start++;
        if(start ==4) {
            compressed[i] = "0";
        }
        else{
            compressed[i] = groups[i]+start;
        }
    }
    // Find the longest run of "0"
    int best_start=-1, best_len=0;
    int current_start=-1, current_len=0;
    for(int i=0;i<8;i++){
        if(strcmp(compressed[i], "0")==0){
            if(current_start==-1){
                current_start =i;
                current_len=1;
            }
            else{
                current_len++;
            }
        }
        else{
            if(current_len > best_len){
                best_len = current_len;
                best_start = current_start;
            }
            current_start = -1;
            current_len=0;
        }
    }
    if(current_len > best_len){
        best_len = current_len;
        best_start = current_start;
    }
    if(best_len <2){
        best_start = -1;
    }
    // Build the output
    char output[100];
    output[0]='\0';
    for(int i=0;i<8;i++){
        if(best_start != -1 && i == best_start){
            if(i ==0){
                strcat(output, "::");
            }
            else{
                strcat(output, ":");
                strcat(output, ":");
            }
            i += best_len -1;
            if(i ==7){
                // Do nothing
            }
            continue;
        }
        if(i !=0){
            strcat(output, ":");
        }
        strcat(output, compressed[i]);
    }
    // Handle the case when all are zeros
    if(best_start ==0 && best_len ==8){
        strcpy(output, "::");
    }
    printf("%s\n", output);
}