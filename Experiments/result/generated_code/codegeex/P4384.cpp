#include <stdio.h>
#include <string.h>

#define MAXN 100005
#define MAXQ 300005

char s[MAXN];
int n, q;
int l[MAXQ], r[MAXQ], ans[MAXQ];

int main() {
    // 读取字符串长度和询问次数
    scanf("%d %d", &n, &q);
    
    // 读取字符串
    scanf("%s", s + 1);
    
    // 读取每个询问的子串范围
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &l[i], &r[i]);
    }
    
    // 处理每个询问
    for (int i = 0; i < q; i++) {
        int len = r[i] - l[i] + 1;
        int cnt = 0;
        
        // 统计子串在原字符串中的出现次数
        for (int j = 1; j <= n - len + 1; j++) {
            int k;
            for (k = 0; k < len; k++) {
                if (s[j + k] != s[l[i] + k]) break;
            }
            if (k == len) cnt++;
        }
        
        // 计算答案
        ans[i] = cnt * (cnt - 1) / 2;
    }
    
    // 输出每个询问的答案
    for (int i = 0; i < q; i++) {
        printf("%d\n", ans[i]);
    }
    
    return 0;
}