#include <stdio.h>
#include <stdlib.h>

#define MAXN 1001

int n, a[MAXN], st1[MAXN], st2[MAXN], top1, top2;
char ops[MAXN * 2];

void push1(int x) {
    st1[++top1] = x;
    ops[top1] = 'a';
}

void pop1() {
    if (top1 == 0) return;
    top1--;
    ops[top1 + 1] = 'b';
}

void push2(int x) {
    st2[++top2] = x;
    ops[top2] = 'c';
}

void pop2() {
    if (top2 == 0) return;
    top2--;
    ops[top2 + 1] = 'd';
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    int j = 1;
    for (int i = 1; i <= n; i++) {
        if (a[i] == j) {
            while (top1 > 0) {
                pop1();
                j++;
            }
            while (top2 > 0) {
                pop2();
                j++;
            }
        } else {
            if (top1 == 0) {
                push1(a[i]);
            } else if (a[i] > st1[top1]) {
                push2(a[i]);
            } else {
                while (top1 > 0 && st1[top1] < a[i]) {
                    push2(st1[top1]);
                    pop1();
                }
                push1(a[i]);
            }
        }
    }

    while (top1 > 0) {
        pop1();
    }
    while (top2 > 0) {
        pop2();
    }

    for (int i = 1; i <= n * 2; i++) {
        if (ops[i] == 0) {
            printf("0\n");
            return 0;
        }
    }

    for (int i = 1; i <= n * 2; i++) {
        printf("%c ", ops[i]);
    }
    printf("\n");

    return 0;
}