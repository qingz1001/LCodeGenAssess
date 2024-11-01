#include <stdio.h>

#define MAX_K 10
#define MAX_N 20

int main() {
    int K, N;
    int rankings[MAX_K][MAX_N];
    int consistent_pairs = 0;
    
    // 读取输入
    scanf("%d %d", &K, &N);
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &rankings[i][j]);
        }
    }
    
    // 检查每一对奶牛
    for (int cow1 = 1; cow1 <= N; cow1++) {
        for (int cow2 = cow1 + 1; cow2 <= N; cow2++) {
            int consistent = 1;
            int first_comparison = -1;
            
            // 检查每次训练课的排名
            for (int k = 0; k < K; k++) {
                int pos1 = -1, pos2 = -1;
                
                // 找到两头奶牛在当前排名中的位置
                for (int j = 0; j < N; j++) {
                    if (rankings[k][j] == cow1) pos1 = j;
                    if (rankings[k][j] == cow2) pos2 = j;
                }
                
                // 确定第一次比较的结果
                if (first_comparison == -1) {
                    first_comparison = (pos1 < pos2) ? 1 : 0;
                }
                // 检查是否与第一次比较结果一致
                else if ((pos1 < pos2) != first_comparison) {
                    consistent = 0;
                    break;
                }
            }
            
            if (consistent) {
                consistent_pairs++;
            }
        }
    }
    
    // 输出结果
    printf("%d\n", consistent_pairs);
    
    return 0;
}