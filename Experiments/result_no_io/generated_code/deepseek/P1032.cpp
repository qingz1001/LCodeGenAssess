#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 21
#define MAX_RULES 6
#define MAX_STEPS 10

typedef struct {
    char from[MAX_LEN];
    char to[MAX_LEN];
} Rule;

typedef struct {
    char str[MAX_LEN];
    int steps;
} State;

int bfs(char *start, char *end, Rule *rules, int rule_count) {
    State queue[10000];
    int front = 0, rear = 0;
    strcpy(queue[rear].str, start);
    queue[rear++].steps = 0;

    while (front < rear) {
        State current = queue[front++];
        if (strcmp(current.str, end) == 0) {
            return current.steps;
        }
        if (current.steps >= MAX_STEPS) {
            continue;
        }

        for (int i = 0; i < rule_count; i++) {
            char *pos = current.str;
            while ((pos = strstr(pos, rules[i].from)) != NULL) {
                int len = strlen(rules[i].from);
                State next;
                strcpy(next.str, current.str);
                strncpy(next.str + (pos - current.str), rules[i].to, strlen(rules[i].to));
                strcpy(next.str + (pos - current.str) + strlen(rules[i].to), pos + len);
                next.steps = current.steps + 1;
                queue[rear++] = next;
                pos += len;
            }
        }
    }
    return -1;
}

int main() {
    char A[MAX_LEN], B[MAX_LEN];
    Rule rules[MAX_RULES];
    int rule_count = 0;

    scanf("%s %s", A, B);
    while (scanf("%s %s", rules[rule_count].from, rules[rule_count].to) != EOF) {
        rule_count++;
    }

    int result = bfs(A, B, rules, rule_count);
    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("NO ANSWER!\n");
    }

    return 0;
}