#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_DIGITS 100000
#define MAX_QUERIES 50000

typedef struct {
    char num[MAX_DIGITS + 1];
    int steps;
} State;

int minSteps(char *s, char *t) {
    int s_len = strlen(s);
    int t_len = strlen(t);

    if (s_len < t_len) return -1;

    int visited[MAX_DIGITS + 1];
    memset(visited, 0, sizeof(visited));

    State queue[MAX_DIGITS * 2];
    int front = 0, rear = 0;

    strcpy(queue[rear].num, s);
    queue[rear].steps = 0;
    rear++;

    while (front < rear) {
        State current = queue[front++];
        if (strcmp(current.num, t) == 0) {
            return current.steps;
        }

        // Rule 1: Swap any two digits
        for (int i = 0; i < s_len - 1; i++) {
            for (int j = i + 1; j < s_len; j++) {
                char new_num[MAX_DIGITS + 1];
                strcpy(new_num, current.num);
                char temp = new_num[i];
                new_num[i] = new_num[j];
                new_num[j] = temp;
                if (!visited[atoi(new_num)]) {
                    visited[atoi(new_num)] = 1;
                    strcpy(queue[rear].num, new_num);
                    queue[rear].steps = current.steps + 1;
                    rear++;
                }
            }
        }

        // Rule 2: Delete any one digit
        for (int i = 0; i < s_len; i++) {
            char new_num[MAX_DIGITS + 1];
            strncpy(new_num, current.num, i);
            strcpy(new_num + i, current.num + i + 1);
            if (!visited[atoi(new_num)]) {
                visited[atoi(new_num)] = 1;
                strcpy(queue[rear].num, new_num);
                queue[rear].steps = current.steps + 1;
                rear++;
            }
        }

        // Rule 3: Insert a digit between any two digits
        for (int i = 0; i < s_len - 1; i++) {
            for (char x = current.num[i] + 1; x < current.num[i + 1]; x++) {
                char new_num[MAX_DIGITS + 1];
                strncpy(new_num, current.num, i + 1);
                new_num[i + 1] = x;
                strcpy(new_num + i + 2, current.num + i + 1);
                if (!visited[atoi(new_num)] && strlen(new_num) <= s_len) {
                    visited[atoi(new_num)] = 1;
                    strcpy(queue[rear].num, new_num);
                    queue[rear].steps = current.steps + 1;
                    rear++;
                }
            }
        }
    }

    return -1;
}

int main() {
    char s[MAX_DIGITS + 1];
    int m;
    scanf("%s", s);
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        char t[MAX_DIGITS + 1];
        scanf("%s", t);
        int result = minSteps(s, t);
        printf("%d\n", result);
    }

    return 0;
}