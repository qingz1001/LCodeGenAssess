#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n, p;
    char S[10001], T[10001];
    
    // 读取输入
    scanf("%d", &n);
    scanf("%s", S);
    scanf("%d", &p);
    
    // 构造T数组，T[i]表示S[i]在S'中的位置
    for (int i = 0; i < n; i++) {
        T[S[i] - 'a'] = i;
    }
    
    // 根据T数组重新构造S
    int j = T[p - 1]; // 从S'中位置p-1的字符开始
    for (int i = 0; i < n; i++) {
        S[i] = S[j];
        j = T[j];
    }
    
    // 输出结果
    printf("%s\n", S);
    
    return 0;
}