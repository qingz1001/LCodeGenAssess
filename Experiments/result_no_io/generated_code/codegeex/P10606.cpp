#include <stdio.h>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

#define MAXN 200005

int n, m;
int a[MAXN];
vector<pair<int, int>> conditions[MAXN];

int main() {
    // 读取输入
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < m; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        conditions[x].emplace_back(x, y);
    }

    // 初始化答案和方向数组
    int ans = 0;
    vector<int> direction(n + 1, 0); // 0 表示未定方向，1 表示正方向，-1 表示负方向

    // 处理每个点的条件
    for (int i = 1; i <= n; ++i) {
        // 处理从 i 到每个 y_i 的条件
        for (auto& condition : conditions[i]) {
            int x = condition.first, y = condition.second;
            // 确保 x > y
            if (x < y) swap(x, y);
            // 检查是否满足条件
            if (direction[x] == 0) {
                // 如果未定方向，则默认为正方向
                direction[x] = 1;
            } else if (direction[x] == -1) {
                // 如果方向与条件不符，则需要改变方向
                ans += a[x];
                direction[x] = 1;
            }
            // 设置方向
            for (int j = x; j < y; ++j) {
                direction[j] = 1;
            }
            for (int j = y; j < x; ++j) {
                direction[j] = -1;
            }
        }
    }

    // 输出结果
    printf("%d\n", ans);
    return 0;
}