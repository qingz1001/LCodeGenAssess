#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 1005
#define MAX_NAME 1005
#define MAX_SPEAKERS 50000

typedef struct {
    char name[MAX_NAME];
} Speaker;

int main(){
    char line[MAX_LINE];
    Speaker speakers[MAX_SPEAKERS];
    int speaker_count = 0;
    char first_person[MAX_NAME] = "";
    int line_number = 0;
    int broken = 0;
    int broken_line = 0;
    char broken_person[MAX_NAME] = "";
    // To track if a speaker has spoken before
    // Simple array of strings
    char **spoken = malloc(sizeof(char*) * MAX_SPEAKERS);
    int spoken_count = 0;
    while(fgets(line, sizeof(line), stdin)){
        // Check for empty line
        if(strcmp(line, "\n") == 0 || strcmp(line, "\r\n") == 0){
            break;
        }
        line_number++;
        // Split sender and message
        char *colon = strchr(line, ':');
        if(!colon){
            continue; // Invalid line, skip
        }
        *colon = '\0';
        char sender[MAX_NAME];
        strcpy(sender, line);
        char *message = colon + 1;
        // Remove possible newline at end
        size_t len = strlen(message);
        if(message[len-1] == '\n') message[len-1] = '\0';
        // Add sender to spoken list
        int already_spoken = 0;
        for(int i=0;i<spoken_count;i++){
            if(strcmp(spoken[i], sender) == 0){
                already_spoken = 1;
                break;
            }
        }
        if(!already_spoken){
            spoken[spoken_count] = malloc(sizeof(char)*(strlen(sender)+1));
            strcpy(spoken[spoken_count], sender);
            spoken_count++;
        }
        if(line_number == 1){
            // First line, extract the first_person from @
            char *at = strchr(message, '@');
            if(at){
                at++;
                // Extract until space or end
                char first_p[MAX_NAME];
                int i=0;
                while(at[i] && at[i]!=' ' && at[i]!='\0'){
                    first_p[i] = at[i];
                    i++;
                }
                first_p[i] = '\0';
                strcpy(first_person, first_p);
            }
        }
        if(!broken && line_number >1){
            // Check the message
            int at_count =0;
            char *ptr = message;
            char at_person[MAX_NAME] = "";
            while(*ptr){
                if(*ptr == '@'){
                    at_count++;
                    // Extract the person after @
                    ptr++;
                    int i=0;
                    while(ptr[i] && ptr[i]!=' ' && ptr[i]!='\0'){
                        at_person[i]=ptr[i];
                        i++;
                    }
                    at_person[i] = '\0';
                }
                ptr++;
            }
            if(at_count !=1 || strcmp(at_person, first_person)!=0){
                // Broken
                broken =1;
                broken_line = line_number;
                strcpy(broken_person, sender);
                // Check if sender had spoken before this line
                int had_spoken_before =0;
                for(int i=0;i<spoken_count-1;i++){
                    if(strcmp(spoken[i], sender)==0){
                        had_spoken_before=1;
                        break;
                    }
                }
                if(had_spoken_before || 1){
                    // Successful
                    printf("Successful @%s attempt\n", broken_person);
                }
                else{
                    // Unsuccessful
                    printf("Unsuccessful @%s attempt\n", broken_person);
                    printf("%d\n", broken_line);
                    printf("%s\n", broken_person);
                }
                break;
            }
        }
    }
    if(!broken){
        printf("Unsuccessful @%s attempt\n", first_person);
        printf("%d\n", spoken_count);
        printf("Good Queue Shape\n");
    }
    // Free allocated memory
    for(int i=0;i<spoken_count;i++) free(spoken[i]);
    free(spoken);
    return 0;
}