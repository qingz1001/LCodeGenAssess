#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 1005

int n, a[MAX_N], s1[MAX_N], s2[MAX_N];
int top1, top2, cur;
char ans[MAX_N * 2];
int ansLen;

bool dfs(int step) {
    if (step == 2 * n) {
        return cur == n + 1;
    }
    
    if (top1 > 0 && s1[top1] == cur) {
        ans[ansLen++] = 'b';
        top1--;
        cur++;
        if (dfs(step + 1)) return true;
        top1++;
        cur--;
        ansLen--;
    }
    
    if (top2 > 0 && s2[top2] == cur) {
        ans[ansLen++] = 'd';
        top2--;
        cur++;
        if (dfs(step + 1)) return true;
        top2++;
        cur--;
        ansLen--;
    }
    
    if (step - top1 - top2 < n) {
        int x = a[step - top1 - top2 + 1];
        if (top1 == 0 || x < s1[top1]) {
            ans[ansLen++] = 'a';
            s1[++top1] = x;
            if (dfs(step + 1)) return true;
            top1--;
            ansLen--;
        }
        
        ans[ansLen++] = 'c';
        s2[++top2] = x;
        if (dfs(step + 1)) return true;
        top2--;
        ansLen--;
    }
    
    return false;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    cur = 1;
    if (dfs(0)) {
        for (int i = 0; i < ansLen; i++) {
            printf("%c%c", ans[i], i == ansLen - 1 ? '\n' : ' ');
        }
    } else {
        printf("0\n");
    }
    
    return 0;
}