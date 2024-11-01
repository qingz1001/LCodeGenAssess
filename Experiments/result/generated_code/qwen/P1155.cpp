#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005

int stack1[MAXN], stack2[MAXN];
int top1 = -1, top2 = -1;

void push(int stack[], int *top, int value) {
    stack[++(*top)] = value;
}

int pop(int stack[], int *top) {
    return stack[(*top)--];
}

int is_empty(int top) {
    return top == -1;
}

void print_sequence(char sequence[], int length) {
    for (int i = 0; i < length; i++) {
        printf("%c", sequence[i]);
        if (i != length - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    char sequence[MAXN];
    int seq_index = 0;

    int target = 1;
    for (int i = 0; i < n; i++) {
        while (!is_empty(top1) && stack1[top1] == target) {
            sequence[seq_index++] = 'b';
            pop(stack1, &top1);
            target++;
        }

        if (arr[i] == target) {
            sequence[seq_index++] = 'b';
            target++;
        } else {
            push(stack1, &top1, arr[i]);
            sequence[seq_index++] = 'a';
        }

        while (!is_empty(top1) && stack1[top1] == target) {
            sequence[seq_index++] = 'b';
            pop(stack1, &top1);
            target++;
        }
    }

    while (!is_empty(top1)) {
        sequence[seq_index++] = 'b';
        pop(stack1, &top1);
    }

    for (int i = 0; i < n; i++) {
        while (!is_empty(top2) && stack2[top2] == target) {
            sequence[seq_index++] = 'd';
            pop(stack2, &top2);
            target++;
        }

        if (arr[n - 1 - i] == target) {
            sequence[seq_index++] = 'd';
            target++;
        } else {
            push(stack2, &top2, arr[n - 1 - i]);
            sequence[seq_index++] = 'c';
        }

        while (!is_empty(top2) && stack2[top2] == target) {
            sequence[seq_index++] = 'd';
            pop(stack2, &top2);
            target++;
        }
    }

    while (!is_empty(top2)) {
        sequence[seq_index++] = 'd';
        pop(stack2, &top2);
    }

    if (target != n + 1) {
        printf("0\n");
    } else {
        print_sequence(sequence, seq_index);
    }

    return 0;
}