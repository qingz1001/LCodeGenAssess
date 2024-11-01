#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 21
#define MAX_RULES 6
#define MAX_QUEUE 1000000

typedef struct {
    char str[MAX_LEN];
    int steps;
} State;

typedef struct {
    char from[MAX_LEN];
    char to[MAX_LEN];
} Rule;

int bfs(char *start, char *end, Rule *rules, int rule_count) {
    State queue[MAX_QUEUE];
    int front = 0, rear = 0;
    State initial = { .steps = 0 };
    strcpy(initial.str, start);
    queue[rear++] = initial;

    while (front < rear) {
        State current = queue[front++];
        if (strcmp(current.str, end) == 0) {
            return current.steps;
        }
        if (current.steps >= 10) {
            continue;
        }

        for (int i = 0; i < rule_count; i++) {
            char *pos = current.str;
            while ((pos = strstr(pos, rules[i].from)) != NULL) {
                State next = { .steps = current.steps + 1 };
                strcpy(next.str, current.str);
                strcpy(next.str + (pos - current.str), rules[i].to);
                strcpy(next.str + (pos - current.str) + strlen(rules[i].to), pos + strlen(rules[i].from));
                queue[rear++] = next;
                pos += strlen(rules[i].from);
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