#include <stdio.h>
#include <stdbool.h>

#define MAXN 25

int n;
int w[MAXN], d[MAXN], a[MAXN][MAXN];
bool possible[MAXN];

int main() {
    // 读取球队数量
    scanf("%d", &n);
    
    // 读取每支球队的胜负场数
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &w[i], &d[i]);
    }
    
    // 读取剩余比赛场次
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    
    // 初始化所有球队的可能状态为假
    for (int i = 0; i < n; i++) {
        possible[i] = false;
    }
    
    // 检查每支球队是否有可能成为冠军
    for (int i = 0; i < n; i++) {
        int totalWins = w[i] + d[i];
        bool canWin = true;
        
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            
            // 计算当前球队和对手的净胜场数
            int netWins = w[j] - d[j];
            
            // 如果对手的净胜场数大于等于当前球队的净胜场数且剩余比赛无法超过这个差距，则当前球队无法成为冠军
            if (netWins >= totalWins && a[i][j] <= totalWins - netWins) {
                canWin = false;
                break;
            }
        }
        
        if (canWin) {
            possible[i] = true;
        }
    }
    
    // 输出所有可能获得冠军的球队编号
    for (int i = 0; i < n; i++) {
        if (possible[i]) {
            printf("%d ", i + 1);
        }
    }
    
    return 0;
}