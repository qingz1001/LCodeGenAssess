#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_M 20
#define MAX_P 100
#define MAX_STATEMENTS_PER_SPEAKER 100
#define MAX_NAME_LEN 21
#define MAX_DAY_LEN 10
#define MAX_CONTENT_LEN 251

typedef enum {
    S_AM_GUILTY,
    S_AM_NOT_GUILTY,
    S_SOMEONE_GUILTY,
    S_SOMEONE_NOT_GUILTY,
    S_TODAY_IS,
    S_OTHER
} statement_type;

typedef struct {
    statement_type type;
    int target_idx; // for S_SOMEONE_GUILTY or S_SOMEONE_NOT_GUILTY
    char day[MAX_DAY_LEN]; // for S_TODAY_IS
} processed_statement;

typedef struct {
    processed_statement statements[MAX_P];
    int count;
} speaker_info;

int main(){
    int M, N, P;
    scanf("%d %d %d", &M, &N, &P);
    char names[MAX_M][MAX_NAME_LEN];
    for(int i=0;i<M;i++){
        scanf("%s", names[i]);
    }
    speaker_info speakers[MAX_M];
    for(int i=0;i<M;i++) {
        speakers[i].count = 0;
    }
    char line[300];
    fgets(line, sizeof(line), stdin); // consume the remaining newline
    for(int i=0;i<P;i++){
        if(!fgets(line, sizeof(line), stdin)) break;
        // Remove trailing newline
        int len = strlen(line);
        if(line[len-1]=='\n') line[len-1] = '\0';
        // Split speaker and statement
        char *colon = strchr(line, ':');
        if(!colon) continue;
        *colon = '\0';
        char *speaker = line;
        char *statement = colon + 2; // skip ": "
        // Find speaker index
        int s_idx = -1;
        for(int j=0;j<M;j++) {
            if(strcmp(speaker, names[j]) == 0){
                s_idx = j;
                break;
            }
        }
        if(s_idx == -1) continue;
        // Parse statement
        processed_statement ps;
        ps.type = S_OTHER;
        ps.target_idx = -1;
        ps.day[0] = '\0';
        if(strcmp(statement, "I am guilty.") == 0){
            ps.type = S_AM_GUILTY;
        }
        else if(strcmp(statement, "I am not guilty.") == 0){
            ps.type = S_AM_NOT_GUILTY;
        }
        else if(strncmp(statement, "Today is ", 9) == 0 && statement[strlen(statement)-1]=='.'){
            char day[MAX_DAY_LEN];
            int sc = sscanf(statement, "Today is %s.", day);
            if(sc ==1){
                strcpy(ps.day, day);
                ps.type = S_TODAY_IS;
            }
        }
        else{
            // Check for "XXX is guilty." or "XXX is not guilty."
            char target[MAX_NAME_LEN];
            if(sscanf(statement, "%s is guilty.", target) ==1){
                // Remove possible trailing characters in target
                int t_len = strlen(target);
                if(target[t_len-1] == '.') target[t_len-1] = '\0';
                // Find target index
                int t_idx = -1;
                for(int j=0;j<M;j++) {
                    if(strcmp(target, names[j]) ==0){
                        t_idx = j;
                        break;
                    }
                }
                if(t_idx != -1){
                    ps.type = S_SOMEONE_GUILTY;
                    ps.target_idx = t_idx;
                }
            }
            else{
                if(sscanf(statement, "%s is not guilty.", target) ==1){
                    // Remove possible trailing characters in target
                    int t_len = strlen(target);
                    if(target[t_len-1] == '.') target[t_len-1] = '\0';
                    // Find target index
                    int t_idx = -1;
                    for(int j=0;j<M;j++) {
                        if(strcmp(target, names[j]) ==0){
                            t_idx = j;
                            break;
                        }
                    }
                    if(t_idx != -1){
                        ps.type = S_SOMEONE_NOT_GUILTY;
                        ps.target_idx = t_idx;
                    }
                }
            }
        }
        if(ps.type != S_OTHER){
            speakers[s_idx].statements[speakers[s_idx].count++] = ps;
        }
    }
    // Define days
    const char *days[] = {"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
    int possible_c[M];
    int possible_c_count =0;
    for(int c=0;c<M;c++){
        bool possible = false;
        for(int d=0; d<7 && !possible; d++){
            int A=0, B=0, C_either=0;
            bool invalid = false;
            for(int s=0;s<M && !invalid;s++){
                if(speakers[s].count ==0){
                    C_either++;
                    continue;
                }
                bool truthful = true;
                for(int st=0; st<speakers[s].count; st++){
                    processed_statement ps = speakers[s].statements[st];
                    bool val;
                    switch(ps.type){
                        case S_AM_GUILTY:
                            val = (s == c);
                            break;
                        case S_AM_NOT_GUILTY:
                            val = (s != c);
                            break;
                        case S_SOMEONE_GUILTY:
                            val = (c == ps.target_idx);
                            break;
                        case S_SOMEONE_NOT_GUILTY:
                            val = (c != ps.target_idx);
                            break;
                        case S_TODAY_IS:
                            val = (strcmp(days[d], ps.day) ==0);
                            break;
                        default:
                            val = false;
                            break;
                    }
                    if(!val){
                        truthful = false;
                        break;
                    }
                }
                bool liar = true;
                for(int st=0; st<speakers[s].count; st++){
                    processed_statement ps = speakers[s].statements[st];
                    bool val;
                    switch(ps.type){
                        case S_AM_GUILTY:
                            val = (s == c);
                            break;
                        case S_AM_NOT_GUILTY:
                            val = (s != c);
                            break;
                        case S_SOMEONE_GUILTY:
                            val = (c == ps.target_idx);
                            break;
                        case S_SOMEONE_NOT_GUILTY:
                            val = (c != ps.target_idx);
                            break;
                        case S_TODAY_IS:
                            val = (strcmp(days[d], ps.day) ==0);
                            break;
                        default:
                            val = false;
                            break;
                    }
                    if(val){
                        liar = false;
                        break;
                    }
                }
                if(truthful && liar){
                    C_either++;
                }
                else if(truthful){
                    B++;
                }
                else if(liar){
                    A++;
                }
                else{
                    invalid = true;
                }
            }
            if(!invalid){
                if(A <= N && N <= A + C_either){
                    possible = true;
                }
            }
        }
        if(possible){
            possible_c[possible_c_count++] = c;
        }
    }
    if(possible_c_count ==0){
        printf("Impossible\n");
    }
    else if(possible_c_count ==1){
        printf("%s\n", names[possible_c[0]]);
    }
    else{
        printf("Cannot Determine\n");
    }
    return 0;
}