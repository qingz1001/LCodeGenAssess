#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1005

int n, a[MAXN], s1[MAXN], s2[MAXN];
int top1, top2, cur, out;
char ans[MAXN * 4];
int len;

int check() {
    top1 = top2 = cur = out = len = 0;
    while (out < n) {
        if (top1 && s1[top1] == out + 1) {
            ans[len++] = 'b';
            top1--;
            out++;
        } else if (top2 && s2[top2] == out + 1) {
            ans[len++] = 'd';
            top2--;
            out++;
        } else if (cur < n) {
            if (a[cur] == out + 1) {
                ans[len++] = 'a';
                ans[len++] = 'b';
                cur++;
                out++;
            } else if (!top1 || a[cur] < s1[top1]) {
                ans[len++] = 'a';
                s1[++top1] = a[cur++];
            } else if (!top2 || a[cur] < s2[top2]) {
                ans[len++] = 'c';
                s2[++top2] = a[cur++];
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }
    return 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    if (check()) {
        for (int i = 0; i < len; i++) {
            printf("%c", ans[i]);
            if (i < len - 1) printf(" ");
        }
        printf("\n");
    } else {
        printf("0\n");
    }
    
    return 0;
}