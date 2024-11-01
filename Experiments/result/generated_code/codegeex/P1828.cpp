#include <stdio.h>
#include <string.h>

#define MAXN 501
#define MAXP 801
#define MAXC 3001

int map[MAXP][MAXP];
int dis[MAXP][MAXP];
int cow[MAXP];
int n, p, c;

int main() {
    int i, j, x, y, z, ans = 0x7fffffff;
    
    // 初始化map和dis数组
    memset(map, 0x7f, sizeof(map));
    memset(dis, 0x7f, sizeof(dis));
    
    // 读取输入
    scanf("%d %d %d", &n, &p, &c);
    for (i = 0; i < n; i++) {
        scanf("%d", &cow[i]);
    }
    for (i = 0; i < c; i++) {
        scanf("%d %d %d", &x, &y, &z);
        if (map[x][y] > z) {
            map[x][y] = map[y][x] = z;
        }
    }
    
    // Floyd-Warshall算法计算所有牧场之间的最短路径
    for (k = 1; k <= p; k++) {
        for (i = 1; i <= p; i++) {
            for (j = 1; j <= p; j++) {
                if (dis[i][j] > dis[i][k] + dis[k][j]) {
                    dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
        }
    }
    
    // 计算每个牧场作为糖放置点的总距离
    for (i = 1; i <= p; i++) {
        int totalDistance = 0;
        for (j = 0; j < n; j++) {
            totalDistance += dis[cow[j]][i];
        }
        if (totalDistance < ans) {
            ans = totalDistance;
        }
    }
    
    // 输出结果
    printf("%d\n", ans);
    
    return 0;
}