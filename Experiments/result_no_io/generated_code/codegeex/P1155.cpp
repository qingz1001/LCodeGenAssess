#include <stdio.h>
#include <stdlib.h>

#define MAXN 1001

int a[MAXN], s1[MAXN], s2[MAXN];
int top1, top2;

void push_s1(int val) {
    s1[++top1] = val;
}

void push_s2(int val) {
    s2[++top2] = val;
}

int pop_s1() {
    return s1[top1--];
}

int pop_s2() {
    return s2[top2--];
}

int is_empty_s1() {
    return top1 == 0;
}

int is_empty_s2() {
    return top2 == 0;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    int j = 1;
    for (int i = 1; i <= n; i++) {
        if (a[i] == j) {
            printf("b ");
            j++;
        } else {
            while (j < a[i]) {
                push_s1(j++);
                printf("a ");
            }
            push_s1(a[i]);
            printf("a ");
            while (!is_empty_s1()) {
                printf("b ");
                j++;
            }
        }

        if (!is_empty_s2()) {
            while (!is_empty_s2()) {
                printf("d ");
                j++;
            }
        }
    }

    while (!is_empty_s1()) {
        printf("b ");
    }

    return 0;
}