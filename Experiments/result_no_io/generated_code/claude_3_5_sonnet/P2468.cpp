#include <stdio.h>
#include <string.h>

#define MAXN 505
#define MAXM 200005

int R, C, M;
int P[MAXN][MAXN];
long long sum[MAXN][MAXN];

void init() {
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + P[i][j];
        }
    }
}

long long getSum(int x1, int y1, int x2, int y2) {
    return sum[x2][y2] - sum[x1-1][y2] - sum[x2][y1-1] + sum[x1-1][y1-1];
}

int solve(int x1, int y1, int x2, int y2, long long H) {
    int left = 1, right = (x2-x1+1) * (y2-y1+1), mid, ans = -1;
    long long total = getSum(x1, y1, x2, y2);
    
    if (total < H) return -1;
    
    while (left <= right) {
        mid = (left + right) / 2;
        int flag = 0;
        
        for (int i = x1; i <= x2 && !flag; i++) {
            for (int j = y1; j <= y2 && !flag; j++) {
                int ex = i + mid - 1, ey = j + mid - 1;
                if (ex > x2) ex = x2;
                if (ey > y2) ey = y2;
                if (getSum(i, j, ex, ey) >= H) flag = 1;
            }
        }
        
        if (flag) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return ans;
}

int main() {
    scanf("%d%d%d", &R, &C, &M);
    
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            scanf("%d", &P[i][j]);
        }
    }
    
    init();
    
    for (int i = 0; i < M; i++) {
        int x1, y1, x2, y2;
        long long H;
        scanf("%d%d%d%d%lld", &x1, &y1, &x2, &y2, &H);
        
        int res = solve(x1, y1, x2, y2, H);
        if (res == -1) {
            printf("Poor QLW\n");
        } else {
            printf("%d\n", res);
        }
    }
    
    return 0;
}