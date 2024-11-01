#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char input[40];
    scanf("%39s", input);
    
    char groups[8][5];
    int idx = 0, g = 0;
    for(int i=0;i<39;i++){
        if(input[i] == ':'){
            groups[g][idx] = '\0';
            g++;
            idx=0;
        }
        else{
            groups[g][idx++] = input[i];
        }
    }
    groups[g][idx] = '\0';
    
    // Find the longest run of "0000"
    int max_len = 0, max_start = -1;
    int current_len = 0, current_start = -1;
    for(int i=0;i<8;i++){
        if(strcmp(groups[i], "0000") == 0){
            if(current_len == 0){
                current_start = i;
            }
            current_len++;
        }
        else{
            if(current_len > max_len){
                max_len = current_len;
                max_start = current_start;
            }
            current_len = 0;
            current_start = -1;
        }
    }
    if(current_len > max_len){
        max_len = current_len;
        max_start = current_start;
    }
    
    // Only compress if the run length is >=2
    if(max_len <2){
        max_start = -1;
    }
    
    // Build the compressed address
    char output[100] = "";
    for(int i=0;i<8;){
        if(i == max_start){
            strcat(output, "::");
            i += max_len;
            if(i >=8){
                break;
            }
        }
        else{
            // Remove leading zeros
            char *ptr = groups[i];
            while(*ptr == '0' && *(ptr+1) != '\0') ptr++;
            strcat(output, ptr);
            i++;
            if(i <8){
                strcat(output, ":");
            }
        }
    }
    
    // Handle special case when the address ends with "::"
    if(output[strlen(output)-1] == ':' && output[strlen(output)-2] == ':'){
        // Do nothing
    }
    // Handle the case when the address starts with "::" and has more characters
    else if(output[0] == ':' && output[1] == ':' && strlen(output)==2){
        // Do nothing
    }
    
    printf("%s\n", output);
}