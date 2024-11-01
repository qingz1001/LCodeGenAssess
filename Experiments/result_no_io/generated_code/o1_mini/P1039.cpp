#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_M 20
#define MAX_P 100
#define MAX_NAME 21
#define MAX_STATEMENTS_PER_SPEAKER 100
#define MAX_LINE 300

typedef struct {
    int type; // 1: I am guilty. 2: I am not guilty. 3: XXX is guilty. 4: XXX is not guilty. 5: Today is XXX.
    int target; // for types 3,4: student index; for type5: day index
} Statement;

int main(){
    int M, N, P;
    scanf("%d %d %d\n", &M, &N, &P);
    
    char names[MAX_M][MAX_NAME];
    for(int i=0;i<M;i++){
        fgets(names[i], MAX_NAME, stdin);
        // Remove trailing newline
        int len = strlen(names[i]);
        if(names[i][len-1]=='\n') names[i][len-1]='\0';
    }
    
    // Prepare statements per speaker
    Statement speaker_statements[MAX_M][MAX_P];
    int speaker_counts[MAX_M];
    for(int i=0;i<M;i++) speaker_counts[i]=0;
    
    // Days mapping
    char *day_names[7] = {"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
    
    char line[MAX_LINE];
    for(int i=0;i<P;i++){
        if(!fgets(line, sizeof(line), stdin)) break;
        // Remove trailing newline
        int len = strlen(line);
        if(line[len-1]=='\n') line[len-1]='\0';
        
        // Split speaker and statement
        char *colon = strchr(line, ':');
        if(!colon) continue;
        *colon = '\0';
        char *speaker_name = line;
        char *statement = colon + 2; // Skip ": "
        
        // Find speaker index
        int speaker = -1;
        for(int j=0; j<M; j++) {
            if(strcmp(speaker_name, names[j]) == 0){
                speaker = j;
                break;
            }
        }
        if(speaker == -1) continue; // Invalid speaker
        
        // Parse statement
        Statement stmt;
        stmt.type = 0;
        stmt.target = -1;
        
        if(strcmp(statement, "I am guilty.") == 0){
            stmt.type = 1;
        }
        else if(strcmp(statement, "I am not guilty.") == 0){
            stmt.type = 2;
        }
        else{
            // Check for "XXX is guilty." or "XXX is not guilty." or "Today is XXX."
            if(strncmp(statement, "Today is ", 9) == 0){
                char day_str[15];
                strcpy(day_str, statement + 9);
                // Remove trailing period
                int l = strlen(day_str);
                if(day_str[l-1]=='.') day_str[l-1]='\0';
                // Find day index
                int day_idx = -1;
                for(int d=0; d<7; d++) {
                    if(strcmp(day_str, day_names[d]) == 0){
                        day_idx = d;
                        break;
                    }
                }
                if(day_idx != -1){
                    stmt.type = 5;
                    stmt.target = day_idx;
                }
            }
            else{
                // Check for "XXX is guilty." or "XXX is not guilty."
                char subject[MAX_NAME];
                if(sscanf(statement, "%s", subject) !=1) continue;
                // Find " is guilty." or " is not guilty."
                char *is_ptr = strstr(statement, " is ");
                if(!is_ptr) continue;
                if(strstr(is_ptr, " is guilty.") == is_ptr){
                    // "XXX is guilty."
                    char name[MAX_NAME];
                    strncpy(name, statement, is_ptr - statement);
                    name[is_ptr - statement] = '\0';
                    // Find name index
                    int target = -1;
                    for(int j=0; j<M; j++) {
                        if(strcmp(name, names[j]) == 0){
                            target = j;
                            break;
                        }
                    }
                    if(target != -1){
                        stmt.type = 3;
                        stmt.target = target;
                    }
                }
                else if(strstr(is_ptr, " is not guilty.") == is_ptr){
                    // "XXX is not guilty."
                    char name[MAX_NAME];
                    strncpy(name, statement, is_ptr - statement);
                    name[is_ptr - statement] = '\0';
                    // Find name index
                    int target = -1;
                    for(int j=0; j<M; j++) {
                        if(strcmp(name, names[j]) == 0){
                            target = j;
                            break;
                        }
                    }
                    if(target != -1){
                        stmt.type = 4;
                        stmt.target = target;
                    }
                }
            }
        }
        if(stmt.type !=0){
            speaker_statements[speaker][speaker_counts[speaker]++] = stmt;
        }
    }
    
    // Possible criminals
    int possible_criminals[MAX_M];
    memset(possible_criminals, 0, sizeof(possible_criminals));
    int criminal_count =0;
    
    for(int criminal=0; criminal<M; criminal++){
        for(int day=0; day<7; day++){
            int liar_count=0;
            int invalid=0;
            for(int speaker=0; speaker<M; speaker++){
                int sc = speaker_counts[speaker];
                if(sc ==0){
                    // No statements, assume truthful
                    continue;
                }
                int all_true =1, all_false=1;
                for(int s=0; s<sc; s++){
                    Statement stmt = speaker_statements[speaker][s];
                    int truth = 0;
                    switch(stmt.type){
                        case 1:
                            // I am guilty.
                            truth = (speaker == criminal) ? 1 : 0;
                            break;
                        case 2:
                            // I am not guilty.
                            truth = (speaker != criminal) ? 1 : 0;
                            break;
                        case 3:
                            // XXX is guilty.
                            truth = (stmt.target == criminal) ? 1 : 0;
                            break;
                        case 4:
                            // XXX is not guilty.
                            truth = (stmt.target != criminal) ? 1 : 0;
                            break;
                        case 5:
                            // Today is XXX.
                            truth = (stmt.target == day) ? 1 : 0;
                            break;
                        default:
                            truth = 0;
                    }
                    if(truth ==0) all_true =0;
                    if(truth ==1) all_false =0;
                }
                if(all_true){
                    // Speaker is truthful
                }
                else if(all_false){
                    // Speaker is liar
                    liar_count++;
                }
                else{
                    // Invalid
                    invalid=1;
                    break;
                }
            }
            if(!invalid && liar_count == N){
                possible_criminals[criminal] =1;
                break; // No need to check other days
            }
        }
    }
    
    // Count possible criminals
    int total=0;
    int last = -1;
    for(int i=0;i<M;i++) if(possible_criminals[i]) {total++; last =i;}
    if(total ==1){
        printf("%s\n", names[last]);
    }
    else if(total >1){
        printf("Cannot Determine\n");
    }
    else{
        printf("Impossible\n");
    }
    
    return 0;
}