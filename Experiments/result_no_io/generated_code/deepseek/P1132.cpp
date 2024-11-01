#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_LEN 6  // 假设最大数字长度为5位，加上'\0'
#define MAX_QUEUE 1000000

typedef struct {
    char num[MAX_LEN];
    int steps;
} State;

typedef struct {
    State data[MAX_QUEUE];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = 0;
}

int isEmpty(Queue *q) {
    return q->front == q->rear;
}

void enqueue(Queue *q, State s) {
    q->data[q->rear++] = s;
}

State dequeue(Queue *q) {
    return q->data[q->front++];
}

int compare(const void *a, const void *b) {
    return *(char *)a - *(char *)b;
}

int minSteps(char *s, char *t) {
    Queue q;
    initQueue(&q);
    State initState = { .steps = 0 };
    strcpy(initState.num, s);
    enqueue(&q, initState);

    int lenS = strlen(s);
    int lenT = strlen(t);
    int visited[100000] = {0};
    visited[atoi(s)] = 1;

    while (!isEmpty(&q)) {
        State current = dequeue(&q);
        if (strcmp(current.num, t) == 0) {
            return current.steps;
        }

        // Rule 1: Swap any two digits
        for (int i = 0; i < lenS - 1; i++) {
            for (int j = i + 1; j < lenS; j++) {
                char newNum[MAX_LEN];
                strcpy(newNum, current.num);
                char temp = newNum[i];
                newNum[i] = newNum[j];
                newNum[j] = temp;
                int newNumInt = atoi(newNum);
                if (!visited[newNumInt]) {
                    visited[newNumInt] = 1;
                    State newState = { .steps = current.steps + 1 };
                    strcpy(newState.num, newNum);
                    enqueue(&q, newState);
                }
            }
        }

        // Rule 2: Delete any one digit
        for (int i = 0; i < lenS; i++) {
            char newNum[MAX_LEN];
            strncpy(newNum, current.num, i);
            strcpy(newNum + i, current.num + i + 1);
            int newNumInt = atoi(newNum);
            if (!visited[newNumInt]) {
                visited[newNumInt] = 1;
                State newState = { .steps = current.steps + 1 };
                strcpy(newState.num, newNum);
                enqueue(&q, newState);
            }
        }

        // Rule 3: Insert a digit between any two digits
        for (int i = 0; i < lenS - 1; i++) {
            for (char x = current.num[i] + 1; x < current.num[i + 1]; x++) {
                char newNum[MAX_LEN];
                strncpy(newNum, current.num, i + 1);
                newNum[i + 1] = x;
                strcpy(newNum + i + 2, current.num + i + 1);
                int newNumInt = atoi(newNum);
                if (!visited[newNumInt] && strlen(newNum) <= lenS) {
                    visited[newNumInt] = 1;
                    State newState = { .steps = current.steps + 1 };
                    strcpy(newState.num, newNum);
                    enqueue(&q, newState);
                }
            }
        }
    }

    return -1;
}

int main() {
    char s[MAX_LEN];
    int m;
    scanf("%s", s);
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        char t[MAX_LEN];
        scanf("%s", t);
        int result = minSteps(s, t);
        printf("%d\n", result);
    }

    return 0;
}