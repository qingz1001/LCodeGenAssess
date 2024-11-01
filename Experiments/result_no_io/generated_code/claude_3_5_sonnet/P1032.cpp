#include <stdio.h>
#include <string.h>

#define MAX_LEN 21
#define MAX_RULES 6
#define MAX_STEPS 10

char A[MAX_LEN], B[MAX_LEN];
char rules[MAX_RULES][2][MAX_LEN];
int rule_count = 0;

int min_steps = MAX_STEPS + 1;

void dfs(char *current, int step) {
    if (step > MAX_STEPS) return;
    if (strcmp(current, B) == 0) {
        if (step < min_steps) min_steps = step;
        return;
    }

    for (int i = 0; i < rule_count; i++) {
        char *found = strstr(current, rules[i][0]);
        if (found) {
            int pos = found - current;
            char new_str[MAX_LEN];
            strncpy(new_str, current, pos);
            new_str[pos] = '\0';
            strcat(new_str, rules[i][1]);
            strcat(new_str, found + strlen(rules[i][0]));
            dfs(new_str, step + 1);
        }
    }
}

int main() {
    scanf("%s %s", A, B);

    while (scanf("%s %s", rules[rule_count][0], rules[rule_count][1]) == 2) {
        rule_count++;
    }

    dfs(A, 0);

    if (min_steps <= MAX_STEPS) {
        printf("%d\n", min_steps);
    } else {
        printf("NO ANSWER!\n");
    }

    return 0;
}