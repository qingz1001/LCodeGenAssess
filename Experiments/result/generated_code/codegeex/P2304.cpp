#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

#define MAXN 100005

struct Point {
    int x, y;
};

int n;
Point trees[MAXN];
int dp[MAXN][3];
int parent[MAXN][3];
int stack[MAXN];
int top;
int result[MAXN];
int cnt;
int ans;

bool cmp(const Point &a, const Point &b) {
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}

void init() {
    sort(trees + 1, trees + n + 1, cmp);
    for (int i = 1; i <= n; i++) {
        dp[i][0] = dp[i][1] = dp[i][2] = 1;
        parent[i][0] = parent[i][1] = parent[i][2] = i;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &trees[i].x, &trees[i].y);
    }

    init();

    for (int i = 2; i <= n; i++) {
        for (int j = i - 1; j >= 1; j--) {
            if (trees[i].x == trees[j].x) {
                if (dp[i][0] < dp[j][0] + 1) continue;
                dp[i][0] = dp[j][0] + 1;
                parent[i][0] = parent[j][0];
            } else if (trees[i].y == trees[j].y) {
                if (dp[i][1] < dp[j][1] + 1) continue;
                dp[i][1] = dp[j][1] + 1;
                parent[i][1] = parent[j][1];
            } else {
                int diff = trees[i].y - trees[j].y;
                int base = trees[i].x - trees[j].x;
                if (diff % base != 0) continue;
                int k = diff / base;
                if (dp[i][2] < dp[j][2] + 1) continue;
                dp[i][2] = dp[j][2] + 1;
                parent[i][2] = parent[j][2];
            }
        }
    }

    int max_val = 0;
    int max_index = 0;
    for (int i = 1; i <= n; i++) {
        if (dp[i][0] > max_val) {
            max_val = dp[i][0];
            max_index = i;
        }
    }

    result[++cnt] = max_index;
    for (int i = 0; i < 3; i++) {
        int current = parent[max_index][i];
        while (current != max_index) {
            result[++cnt] = current;
            current = parent[current][i];
        }
    }

    printf("%d\n", cnt);
    for (int i = cnt; i >= 1; i--) {
        printf("%d ", result[i]);
    }
    printf("\n");

    top = 0;
    for (int i = 1; i <= n; i++) {
        if (trees[i].x != trees[i + 1].x) {
            while (top > 0 && trees[i].x - trees[stack[top]].x > 1) {
                ans++;
                top--;
            }
            if (top > 0) {
                ans++;
            }
            if (trees[i].x - trees[stack[top]].x == 1) {
                int j = stack[top];
                if (trees[i].y > trees[j].y) {
                    if (dp[j][2] > dp[i][2]) {
                        ans++;
                    }
                } else {
                    if (dp[j][1] > dp[i][1]) {
                        ans++;
                    }
                }
            }
            stack[++top] = i;
        }
    }

    printf("%d\n", ans);
    return 0;
}