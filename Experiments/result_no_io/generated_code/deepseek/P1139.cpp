#include <stdio.h>
#include <string.h>

#define MAXN 15

char A[MAXN + 1], B[MAXN + 1], C[MAXN + 1], D[MAXN + 1];
int topA, topB, topC, topD;

void push(char *stack, int *top, char c) {
    stack[++(*top)] = c;
}

char pop(char *stack, int *top) {
    return stack[(*top)--];
}

int is_empty(int top) {
    return top == 0;
}

int is_possible(int n, char *target) {
    int i, j;
    char temp[MAXN + 1];
    int topTemp = 0;

    for (i = 0, j = 0; i < n; i++) {
        if (!is_empty(topA) && A[topA] == target[j]) {
            push(temp, &topTemp, pop(A, &topA));
            j++;
        } else if (!is_empty(topB) && B[topB] == target[j]) {
            push(temp, &topTemp, pop(B, &topB));
            j++;
        } else if (!is_empty(topC) && C[topC] == target[j]) {
            push(temp, &topTemp, pop(C, &topC));
            j++;
        } else if (!is_empty(topD) && D[topD] == target[j]) {
            push(temp, &topTemp, pop(D, &topD));
            j++;
        } else {
            if (!is_empty(topA)) {
                push(B, &topB, pop(A, &topA));
            } else if (!is_empty(topB)) {
                push(C, &topC, pop(B, &topB));
            } else if (!is_empty(topC)) {
                push(D, &topD, pop(C, &topC));
            } else {
                return 0;
            }
        }
    }

    while (j < n) {
        if (!is_empty(topD) && D[topD] == target[j]) {
            push(temp, &topTemp, pop(D, &topD));
            j++;
        } else {
            return 0;
        }
    }

    return 1;
}

void print_operations(int n, char *target) {
    int i;
    for (i = 0; i < n; i++) {
        if (!is_empty(topA) && A[topA] == target[i]) {
            printf("%c A D\n", pop(A, &topA));
        } else if (!is_empty(topB) && B[topB] == target[i]) {
            printf("%c B D\n", pop(B, &topB));
        } else if (!is_empty(topC) && C[topC] == target[i]) {
            printf("%c C D\n", pop(C, &topC));
        } else if (!is_empty(topD) && D[topD] == target[i]) {
            printf("%c D D\n", pop(D, &topD));
        }
    }
}

int main() {
    int n, i;
    char target[MAXN + 1];

    scanf("%d %s", &n, target);

    for (i = n - 1; i >= 0; i--) {
        push(A, &topA, target[i]);
    }

    if (is_possible(n, target)) {
        print_operations(n, target);
    } else {
        printf("NO\n");
    }

    return 0;
}