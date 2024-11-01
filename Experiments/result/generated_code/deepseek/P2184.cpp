#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n, m;
int diff[MAXN] = {0}; // 差分数组
int count[MAXN] = {0}; // 记录每个位置的地雷种类数

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < m; i++) {
        int q, l, r;
        scanf("%d %d %d", &q, &l, &r);
        
        if (q == 1) {
            // 布雷操作
            diff[l]++;
            if (r + 1 <= n) diff[r + 1]--;
        } else if (q == 2) {
            // 查询操作
            int total = 0;
            for (int j = 1; j <= r; j++) {
                count[j] += diff[j];
                if (j >= l && j <= r) {
                    total += (count[j] > 0);
                }
            }
            printf("%d\n", total);
        }
    }
    
    return 0;
}