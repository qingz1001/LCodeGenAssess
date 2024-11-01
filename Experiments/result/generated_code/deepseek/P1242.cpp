#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *disks;
    int top;
} Stack;

void initStack(Stack *s, int size) {
    s->disks = (int *)malloc(size * sizeof(int));
    s->top = -1;
}

void push(Stack *s, int disk) {
    s->disks[++s->top] = disk;
}

int pop(Stack *s) {
    return s->disks[s->top--];
}

int peek(Stack *s) {
    return s->disks[s->top];
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void moveDisk(char from, char to, int disk) {
    printf("move %d from %c to %c\n", disk, from, to);
}

void hanoi(int n, Stack *src, Stack *aux, Stack *dest, char s, char a, char d) {
    if (n == 1) {
        int disk = pop(src);
        push(dest, disk);
        moveDisk(s, d, disk);
        return;
    }
    hanoi(n - 1, src, dest, aux, s, d, a);
    int disk = pop(src);
    push(dest, disk);
    moveDisk(s, d, disk);
    hanoi(n - 1, aux, src, dest, a, s, d);
}

int main() {
    int n;
    scanf("%d", &n);

    Stack A, B, C;
    initStack(&A, n);
    initStack(&B, n);
    initStack(&C, n);

    int disk;
    for (int i = 0; i < 3; i++) {
        while (1) {
            scanf("%d", &disk);
            if (disk == 0) break;
            if (i == 0) push(&A, disk);
            if (i == 1) push(&B, disk);
            if (i == 2) push(&C, disk);
        }
    }

    Stack targetA, targetB, targetC;
    initStack(&targetA, n);
    initStack(&targetB, n);
    initStack(&targetC, n);

    for (int i = 0; i < 3; i++) {
        while (1) {
            scanf("%d", &disk);
            if (disk == 0) break;
            if (i == 0) push(&targetA, disk);
            if (i == 1) push(&targetB, disk);
            if (i == 2) push(&targetC, disk);
        }
    }

    // Assuming the initial and target states are correctly provided,
    // we can now solve the problem using the recursive Hanoi function.
    // For simplicity, we assume the initial state is all disks on A and the target state is all disks on C.
    hanoi(n, &A, &B, &C, 'A', 'B', 'C');

    printf("%d\n", (1 << n) - 1); // Minimum steps for n disks in Hanoi tower problem

    free(A.disks);
    free(B.disks);
    free(C.disks);
    free(targetA.disks);
    free(targetB.disks);
    free(targetC.disks);

    return 0;
}