#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <algorithm>

using namespace std;

const int N = 1000005;
int n, l[N], r[N], f[N], ans;

int main() {
    // 读取输入
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &l[i], &r[i]);
    }

    // 初始化f数组，f[i]表示前i个格子的最小腐蚀代价
    memset(f, 0x3f, sizeof(f)); // 使用0x3f3f3f3f表示无穷大
    f[0] = 0; // 初始状态，没有腐蚀代价

    // 动态规划求解最小腐蚀代价
    for (int i = 1; i <= n; i++) {
        // 更新f[i]，直接腐蚀当前格子
        f[i] = min(f[i], f[i-1] + 1);

        // 更新f[i]，将当前格子与前面的格子合并
        for (int j = i-1; j >= 1; j--) {
            if (r[j] >= l[i] && r[i] >= l[j]) {
                f[i] = min(f[i], f[j-1] + (i-j-1));
            } else {
                break;
            }
        }
    }

    // 找到最小的腐蚀代价
    ans = INT_MAX;
    for (int i = 1; i <= n; i++) {
        ans = min(ans, f[i]);
    }

    // 输出结果
    printf("%d\n", ans);
    return 0;
}