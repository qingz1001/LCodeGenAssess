#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1005

int n;
int a[MAXN];
int s1[MAXN], s2[MAXN];
int top1 = 0, top2 = 0;
char result[MAXN * 2];
int result_len = 0;

void push_s1(int x) {
    s1[++top1] = x;
    result[result_len++] = 'a';
}

void pop_s1() {
    top1--;
    result[result_len++] = 'b';
}

void push_s2(int x) {
    s2[++top2] = x;
    result[result_len++] = 'c';
}

void pop_s2() {
    top2--;
    result[result_len++] = 'd';
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int next = 1;
    int i = 0;
    while (i < n || top1 > 0 || top2 > 0) {
        if (top1 > 0 && s1[top1] == next) {
            pop_s1();
            next++;
        } else if (top2 > 0 && s2[top2] == next) {
            pop_s2();
            next++;
        } else if (i < n && a[i] == next) {
            push_s1(a[i]);
            pop_s1();
            next++;
            i++;
        } else if (i < n && (top1 == 0 || a[i] < s1[top1])) {
            push_s1(a[i]);
            i++;
        } else if (i < n && (top2 == 0 || a[i] < s2[top2])) {
            push_s2(a[i]);
            i++;
        } else {
            printf("0\n");
            return 0;
        }
    }

    for (int j = 0; j < result_len; j++) {
        printf("%c", result[j]);
        if (j < result_len - 1) {
            printf(" ");
        }
    }
    printf("\n");

    return 0;
}