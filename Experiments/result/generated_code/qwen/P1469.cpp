#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    
    // 使用异或运算来找出唯一的数字
    int result = 0;
    for (int i = 0; i < n; i++) {
        int length;
        scanf("%d", &length);
        result ^= length;
    }
    
    printf("%d\n", result);
    
    return 0;
}