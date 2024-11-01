#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RULES 6
#define MAX_STRING_LENGTH 100
#define MAX_QUEUE_SIZE 1000000
#define MAX_VISITED 1000000

typedef struct {
    char str[MAX_STRING_LENGTH];
    int step;
} QueueNode;

int main(){
    char A[MAX_STRING_LENGTH], B[MAX_STRING_LENGTH];
    char rules_src[MAX_RULES][21], rules_dst[MAX_RULES][21];
    int num_rules =0;
    
    // Read A and B
    if(scanf("%s %s", A, B)!=2){
        return 0;
    }
    
    // Read substitution rules
    while(scanf("%s %s", rules_src[num_rules], rules_dst[num_rules]) != EOF){
        num_rules++;
        if(num_rules >= MAX_RULES) break;
    }
    
    // Initialize visited
    char visited[MAX_VISITED][MAX_STRING_LENGTH];
    int visited_count =0;
    strcpy(visited[visited_count++], A);
    
    // Initialize queue
    QueueNode queue[MAX_QUEUE_SIZE];
    int head =0, tail=0;
    strcpy(queue[tail].str, A);
    queue[tail].step =0;
    tail++;
    
    int found =0;
    
    while(head < tail){
        QueueNode current = queue[head];
        head++;
        
        if(strcmp(current.str, B)==0){
            printf("%d\n", current.step);
            return 0;
        }
        
        if(current.step >=10){
            continue;
        }
        
        for(int r=0;r<num_rules;r++){
            char *pos = current.str;
            int len_src = strlen(rules_src[r]);
            while((pos = strstr(pos, rules_src[r])) != NULL){
                int index = pos - current.str;
                char new_str[MAX_STRING_LENGTH];
                // Replace at index
                // Copy up to index
                strncpy(new_str, current.str, index);
                new_str[index] = '\0';
                // Append replacement
                strcat(new_str, rules_dst[r]);
                // Append the rest after the pattern
                strcat(new_str, current.str + index + len_src);
                
                // Check if visited
                int already =0;
                for(int v=0; v<visited_count; v++){
                    if(strcmp(visited[v], new_str)==0){
                        already =1;
                        break;
                    }
                }
                if(!already){
                    if(visited_count < MAX_VISITED){
                        strcpy(visited[visited_count++], new_str);
                    }
                    // Enqueue
                    if(tail < MAX_QUEUE_SIZE){
                        strcpy(queue[tail].str, new_str);
                        queue[tail].step = current.step +1;
                        tail++;
                        // Check if it is the target
                        if(strcmp(new_str, B)==0){
                            printf("%d\n", current.step +1);
                            return 0;
                        }
                    }
                }
                pos +=1;
            }
        }
    }
    printf("NO ANSWER!\n");
    return 0;
}