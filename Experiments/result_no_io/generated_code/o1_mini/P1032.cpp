#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RULES 6
#define MAX_LEN 21
#define MAX_QUEUE 100000
#define MAX_VISITED 100000

typedef struct {
    char str[MAX_LEN];
    int step;
} Node;

char rules_A[MAX_RULES][MAX_LEN];
char rules_B[MAX_RULES][MAX_LEN];
int rule_count = 0;

Node queue[MAX_QUEUE];
int front = 0, rear = 0;

char visited_strings[MAX_VISITED][MAX_LEN];
int visited_count = 0;

int is_visited(char *s) {
    for(int i=0;i<visited_count;i++) {
        if(strcmp(visited_strings[i], s)==0) return 1;
    }
    return 0;
}

void add_visited(char *s) {
    if(visited_count < MAX_VISITED){
        strcpy(visited_strings[visited_count++], s);
    }
}

int main(){
    char A[MAX_LEN], B[MAX_LEN];
    scanf("%s %s", A, B);
    while(scanf("%s %s", rules_A[rule_count], rules_B[rule_count]) != EOF){
        rule_count++;
        if(rule_count >= MAX_RULES) break;
    }
    front = 0;
    rear = 0;
    strcpy(queue[rear].str, A);
    queue[rear].step = 0;
    rear++;
    add_visited(A);
    while(front < rear){
        Node current = queue[front++];
        if(strcmp(current.str, B) == 0){
            printf("%d\n", current.step);
            return 0;
        }
        if(current.step >=10) continue;
        for(int r=0;r<rule_count;r++){
            int lenA = strlen(rules_A[r]);
            int lenS = strlen(current.str);
            for(int i=0;i<=lenS - lenA;i++){
                if(strncmp(&current.str[i], rules_A[r], lenA) == 0){
                    char new_str[MAX_LEN] = {0};
                    strncpy(new_str, current.str, i);
                    new_str[i] = '\0';
                    strcat(new_str, rules_B[r]);
                    strcat(new_str, &current.str[i + lenA]);
                    if(!is_visited(new_str)){
                        strcpy(queue[rear].str, new_str);
                        queue[rear].step = current.step +1;
                        rear++;
                        add_visited(new_str);
                        if(rear >= MAX_QUEUE) break;
                    }
                }
            }
            if(rear >= MAX_QUEUE) break;
        }
    }
    printf("NO ANSWER!\n");
    return 0;
}