#include <stdio.h>
#include <string.h>

#define MAXN 100005

char str[MAXN];
int val[MAXN], sum[MAXN], cnt[MAXN], n, tot, ans;
int l[MAXN], r[MAXN];

int main() {
    // 读取输入字符串
    scanf("%s", str + 1);
    n = strlen(str + 1);

    // 读取每个矿石的重要度
    for (int i = 1; i <= n; i++) {
        scanf("%d", &val[i]);
    }

    // 计算前缀和
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + val[i];
    }

    // 计算每个后缀的字典序排名
    for (int i = n; i >= 1; i--) {
        cnt[str[i] - 'a']++;
        for (int j = 0; j < 26; j++) {
            cnt[j] += cnt[j + 1];
        }
        l[i] = cnt[str[i] - 'a'];
    }

    // 计算每个前缀的字典序排名
    for (int i = 1; i <= n; i++) {
        cnt[str[i] - 'a']++;
        for (int j = 0; j < 26; j++) {
            cnt[j] += cnt[j + 1];
        }
        r[i] = cnt[str[i] - 'a'];
    }

    // 枚举左端点
    for (int i = 1; i <= n; i++) {
        int j = i;
        while (j <= n && sum[j] - sum[i - 1] >= l[j] && sum[j] - sum[i - 1] <= r[j]) {
            j++;
        }
        j--;
        if (sum[j] - sum[i - 1] == l[j]) {
            ans++;
            printf("%d %d\n", i, j);
        }
    }

    // 输出结果
    printf("%d\n", ans);
    return 0;
}