#include <stdio.h>
#include <stdlib.h>

int n, b, d;
int *ans;
int ansSize;

int check(int num) {
    for (int i = 0; i < ansSize; i++) {
        int dist = 0;
        int x = ans[i], y = num;
        for (int j = 0; j < b; j++) {
            if ((x & 1) != (y & 1)) dist++;
            x >>= 1;
            y >>= 1;
        }
        if (dist < d) return 0;
    }
    return 1;
}

void dfs(int cur, int last) {
    if (cur == b) {
        if (check(last)) {
            ans[ansSize++] = last;
            for (int i = 0; i < ansSize; i++) {
                printf("%d ", ans[i]);
                if (i % 10 == 9) printf("\n");
            }
            if (ansSize % 10 != 0) printf("\n");
        }
        return;
    }
    dfs(cur + 1, last);
    if (cur == 0 || (last & (1 << cur - 1))) {
        last |= (1 << cur);
        dfs(cur + 1, last);
        last &= ~(1 << cur);
    }
}

int main() {
    scanf("%d%d%d", &n, &b, &d);
    ans = (int*)malloc(n * sizeof(int));
    ansSize = 0;
    dfs(0, 0);
    free(ans);
    return 0;
}