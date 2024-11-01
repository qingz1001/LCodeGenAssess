#include <stdio.h>

int a, b, c;
int vis[21][21]; // 用于记录状态是否已经访问过

void dfs(int A, int B, int C) {
    if (vis[A][C]) return; // 如果状态已经访问过，则返回
    vis[A][C] = 1; // 标记当前状态为已访问

    if (A == 0) { // 如果a桶为空，则记录c桶的牛奶量
        printf("%d ", C);
    }

    // 从a桶倒入b桶
    if (A > 0 && B < b) {
        int transfer = (A > b - B) ? b - B : A;
        dfs(A - transfer, B + transfer, C);
    }

    // 从a桶倒入c桶
    if (A > 0 && C < c) {
        int transfer = (A > c - C) ? c - C : A;
        dfs(A - transfer, B, C + transfer);
    }

    // 从b桶倒入a桶
    if (B > 0 && A < a) {
        int transfer = (B > a - A) ? a - A : B;
        dfs(A + transfer, B - transfer, C);
    }

    // 从b桶倒入c桶
    if (B > 0 && C < c) {
        int transfer = (B > c - C) ? c - C : B;
        dfs(A, B - transfer, C + transfer);
    }

    // 从c桶倒入a桶
    if (C > 0 && A < a) {
        int transfer = (C > a - A) ? a - A : C;
        dfs(A + transfer, B, C - transfer);
    }

    // 从c桶倒入b桶
    if (C > 0 && B < b) {
        int transfer = (C > b - B) ? b - B : C;
        dfs(A, B + transfer, C - transfer);
    }
}

int main() {
    scanf("%d%d%d", &a, &b, &c);
    dfs(0, 0, c); // 从c桶开始倒牛奶
    return 0;
}