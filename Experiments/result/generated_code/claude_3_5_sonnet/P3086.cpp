#include <stdio.h>
#include <string.h>

#define MAX_N 300
#define MAX(a,b) ((a)>(b)?(a):(b))

char marble[MAX_N][MAX_N+1];
int sum[MAX_N+1][MAX_N+1];
int n;

long long solve() {
    long long ans = -1;
    
    // 预处理前缀和
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + (marble[i-1][j-1] == '.');
        }
    }

    // 枚举上矩形的上下边界
    for (int top = 1; top <= n-3; top++) {
        for (int bottom = top+1; bottom <= n-2; bottom++) {
            int width = 0;
            long long upper = 0, lower = 0;
            
            // 从左到右扫描
            for (int right = 1; right <= n; right++) {
                if (sum[bottom][right] - sum[top-1][right] - sum[bottom][right-1] + sum[top-1][right-1] == bottom-top+1) {
                    width++;
                    upper = MAX(upper, (long long)(bottom-top-1) * width);
                    
                    // 枚举下矩形的下边界
                    for (int lower_bottom = bottom+1; lower_bottom <= n; lower_bottom++) {
                        if (sum[lower_bottom][right] - sum[bottom][right] - sum[lower_bottom][right-1] + sum[bottom][right-1] == lower_bottom-bottom) {
                            lower = MAX(lower, (long long)(lower_bottom-bottom-1) * width);
                            ans = MAX(ans, upper * lower);
                        } else {
                            break;
                        }
                    }
                } else {
                    width = 0;
                    upper = lower = 0;
                }
            }
        }
    }
    
    return ans;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", marble[i]);
    }
    
    long long result = solve();
    printf("%lld\n", result);
    
    return 0;
}