#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1005

typedef struct {
    int data[MAXN];
    int top;
} Stack;

void push(Stack *s, int x) {
    s->data[++(s->top)] = x;
}

int pop(Stack *s) {
    return s->data[(s->top)--];
}

int is_empty(Stack *s) {
    return s->top == -1;
}

int top(Stack *s) {
    return s->data[s->top];
}

int main() {
    int n;
    int a[MAXN];
    Stack s1, s2;
    s1.top = s2.top = -1;
    char operations[MAXN * 2];
    int op_count = 0;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int expected = 1;
    int i = 0;

    while (expected <= n) {
        if (!is_empty(&s1) && top(&s1) == expected) {
            pop(&s1);
            operations[op_count++] = 'b';
            expected++;
        } else if (!is_empty(&s2) && top(&s2) == expected) {
            pop(&s2);
            operations[op_count++] = 'd';
            expected++;
        } else if (i < n && a[i] == expected) {
            operations[op_count++] = 'a';
            operations[op_count++] = 'b';
            i++;
            expected++;
        } else if (i < n) {
            if (is_empty(&s1) || a[i] < top(&s1)) {
                push(&s1, a[i]);
                operations[op_count++] = 'a';
                i++;
            } else if (is_empty(&s2) || a[i] < top(&s2)) {
                push(&s2, a[i]);
                operations[op_count++] = 'c';
                i++;
            } else {
                printf("0\n");
                return 0;
            }
        } else {
            printf("0\n");
            return 0;
        }
    }

    for (int j = 0; j < op_count; j++) {
        printf("%c", operations[j]);
        if (j < op_count - 1) {
            printf(" ");
        }
    }
    printf("\n");

    return 0;
}