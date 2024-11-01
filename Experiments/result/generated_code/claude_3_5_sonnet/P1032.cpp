#include <stdio.h>
#include <string.h>

#define MAX_LEN 21
#define MAX_RULES 6
#define MAX_STEPS 10

char A[MAX_LEN], B[MAX_LEN];
char rules[MAX_RULES][2][MAX_LEN];
int rule_count = 0;

int dfs(char* current, int depth) {
    if (depth > MAX_STEPS) return -1;
    if (strcmp(current, B) == 0) return depth;

    int min_steps = -1;
    char temp[MAX_LEN];
    
    for (int i = 0; i < rule_count; i++) {
        char* found = strstr(current, rules[i][0]);
        while (found) {
            strcpy(temp, current);
            int pos = found - current;
            int len1 = strlen(rules[i][0]);
            int len2 = strlen(rules[i][1]);
            
            memmove(temp + pos + len2, temp + pos + len1, strlen(temp) - pos - len1 + 1);
            memcpy(temp + pos, rules[i][1], len2);
            
            int result = dfs(temp, depth + 1);
            if (result != -1 && (min_steps == -1 || result < min_steps)) {
                min_steps = result;
            }
            
            found = strstr(found + 1, rules[i][0]);
        }
    }
    
    return min_steps;
}

int main() {
    scanf("%s %s", A, B);
    
    while (scanf("%s %s", rules[rule_count][0], rules[rule_count][1]) == 2) {
        rule_count++;
    }
    
    int result = dfs(A, 0);
    
    if (result == -1) {
        printf("NO ANSWER!\n");
    } else {
        printf("%d\n", result);
    }
    
    return 0;
}