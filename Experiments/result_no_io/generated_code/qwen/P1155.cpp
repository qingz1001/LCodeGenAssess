#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1005

int stack1[MAXN], stack2[MAXN];
int top1 = -1, top2 = -1;
char operations[MAXN * 2];

void push(int stack[], int *top, int value) {
    stack[++(*top)] = value;
}

int pop(int stack[], int *top) {
    return stack[(*top)--];
}

int is_empty(int top) {
    return top == -1;
}

void print_operations() {
    for (int i = 0; i < strlen(operations); i++) {
        printf("%c", operations[i]);
        if (i < strlen(operations) - 1) {
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

    int output_index = 0;
    int current_value = 1;

    for (int i = 0; i < n; i++) {
        while (!is_empty(top1) && stack1[top1] == current_value) {
            push(stack2, &top2, pop(stack1, &top1));
            strcat(operations, "d");
        }

        if (arr[i] != current_value) {
            push(stack1, &top1, arr[i]);
            strcat(operations, "a");
        } else {
            push(stack2, &top2, arr[i]);
            strcat(operations, "c");

            while (!is_empty(top2) && stack2[top2] == current_value) {
                pop(stack2, &top2);
                strcat(operations, "d");
                current_value++;
            }
        }
    }

    while (!is_empty(top1)) {
        push(stack2, &top2, pop(stack1, &top1));
        strcat(operations, "d");
    }

    for (int i = 0; i < n; i++) {
        while (!is_empty(top2) && stack2[top2] == current_value) {
            pop(stack2, &top2);
            strcat(operations, "d");
            current_value++;
        }
    }

    if (current_value == n + 1) {
        print_operations();
    } else {
        printf("0\n");
    }

    return 0;
}