#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 21
#define MAX_RULES 7

typedef struct {
    char from[MAX_LEN];
    char to[MAX_LEN];
} Rule;

int bfs(char *A, char *B, Rule rules[], int num_rules) {
    if (strcmp(A, B) == 0) return 0;
    
    char queue[MAX_RULES][MAX_LEN];
    int front = 0, rear = 0;
    strcpy(queue[rear++], A);
    
    for (int step = 1; step <= 10; step++) {
        int size = rear - front;
        while (size--) {
            char current[MAX_LEN];
            strcpy(current, queue[front++]);
            
            for (int i = 0; i < num_rules; i++) {
                char *pos = strstr(current, rules[i].from);
                if (pos != NULL) {
                    char new_str[MAX_LEN];
                    strncpy(new_str, current, pos - current);
                    strcat(new_str, rules[i].to);
                    strcat(new_str, pos + strlen(rules[i].from));
                    
                    if (strcmp(new_str, B) == 0) return step;
                    
                    strcpy(queue[rear++], new_str);
                }
            }
        }
    }
    
    return -1;
}

int main() {
    char A[MAX_LEN], B[MAX_LEN];
    scanf("%s %s", A, B);
    
    Rule rules[MAX_RULES];
    int num_rules = 0;
    while (scanf("%s %s", rules[num_rules].from, rules[num_rules].to) != EOF) {
        num_rules++;
    }
    
    int result = bfs(A, B, rules, num_rules);
    if (result != -1) printf("%d\n", result);
    else printf("NO ANSWER!\n");
    
    return 0;
}