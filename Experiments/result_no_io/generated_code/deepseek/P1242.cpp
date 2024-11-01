#include <stdio.h>
#include <stdlib.h>

#define MAXN 45

typedef struct {
    int top;
    int data[MAXN];
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAXN - 1;
}

void push(Stack *s, int value) {
    if (!isFull(s)) {
        s->data[++(s->top)] = value;
    }
}

int pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[(s->top)--];
    }
    return -1;
}

int peek(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[s->top];
    }
    return -1;
}

void move(int disk, char from, char to, int *step) {
    printf("move %d from %c to %c\n", disk, from, to);
    (*step)++;
}

void hanoi(int n, Stack *src, Stack *aux, Stack *dest, char s, char a, char d, int *step) {
    if (n == 1) {
        int disk = pop(src);
        push(dest, disk);
        move(disk, s, d, step);
    } else {
        hanoi(n - 1, src, dest, aux, s, d, a, step);
        int disk = pop(src);
        push(dest, disk);
        move(disk, s, d, step);
        hanoi(n - 1, aux, src, dest, a, s, d, step);
    }
}

int main() {
    int n;
    scanf("%d", &n);

    Stack A, B, C;
    initStack(&A);
    initStack(&B);
    initStack(&C);

    int i, disk;
    for (i = 0; i < 3; i++) {
        scanf("%d", &disk);
        if (disk != 0) push(&A, disk);
    }
    for (i = 0; i < 3; i++) {
        scanf("%d", &disk);
        if (disk != 0) push(&B, disk);
    }
    for (i = 0; i < 3; i++) {
        scanf("%d", &disk);
        if (disk != 0) push(&C, disk);
    }

    int step = 0;
    hanoi(n, &A, &B, &C, 'A', 'B', 'C', &step);

    printf("%d\n", step);

    return 0;
}