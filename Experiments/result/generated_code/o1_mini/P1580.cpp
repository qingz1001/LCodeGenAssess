#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 1005

int main(){
    char line[MAX_LINE];
    char initial_mention[MAX_LINE] = "";
    char broken_by[MAX_LINE] = "";
    int line_num = 0;
    int broken = 0;
    int successful = 0;
    int broken_line = 0;
    char broken_id[MAX_LINE] = "";
    
    // Read first line
    if(fgets(line, sizeof(line), stdin)){
        line_num++;
        // Split sender and message
        char *colon = strchr(line, ':');
        if(!colon){
            // Invalid format
            return 0;
        }
        *colon = '\0';
        char *sender = line;
        char *message = colon + 1;
        // Count '@' in message
        int at_count = 0;
        char *p = message;
        char mention[MAX_LINE] = "";
        while(*p){
            if(*p == '@'){
                at_count++;
                // Extract the mention
                sscanf(p+1, "%s", mention);
            }
            p++;
        }
        if(at_count == 1){
            strcpy(initial_mention, mention);
        }
        else{
            // According to the problem, first line always has exactly one '@'
            return 0;
        }
    }
    
    while(fgets(line, sizeof(line), stdin)){
        if(line[0] == '\n') break;
        line_num++;
        // Split sender and message
        char *colon = strchr(line, ':');
        if(!colon){
            // Invalid format
            continue;
        }
        *colon = '\0';
        char *sender = line;
        char *message = colon + 1;
        // Count '@' in message
        int at_count = 0;
        char mentions[100][MAX_LINE];
        int m = 0;
        char *p = message;
        while(*p){
            if(*p == '@'){
                at_count++;
                if(m < 100){
                    sscanf(p+1, "%s", mentions[m]);
                    m++;
                }
            }
            p++;
        }
        if(at_count != 1){
            if(!broken){
                broken = 1;
                strcpy(broken_by, sender);
                broken_line = line_num;
            }
        }
        else{
            if(strcmp(mentions[0], initial_mention)!=0){
                if(!broken){
                    broken = 1;
                    strcpy(broken_by, sender);
                    broken_line = line_num;
                }
            }
        }
        if(broken){
            // Determine if successful
            // Successful if broken by Huntfire, redbag, absi2011
            if(strcmp(broken_by, "yyy loves OI")==0 || strcmp(broken_by, "yyy loves Maths")==0 || strcmp(broken_by, "yyy loves Chemistry")==0){
                successful = 1;
            }
            break;
        }
    }
    
    if(broken){
        if(successful){
            printf("Successful @%s attempt\n", initial_mention);
        }
        else{
            printf("Unsuccessful @%s attempt\n", initial_mention);
            printf("%d\n%s\n", broken_line, broken_by);
        }
    }
    else{
        // Count total messages
        int total = line_num+1; // including first line
        printf("Unsuccessful @%s attempt\n", initial_mention);
        printf("%d\nGood Queue Shape\n", total);
    }
    
    return 0;
}