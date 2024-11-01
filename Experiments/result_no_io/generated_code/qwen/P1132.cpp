#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 60000

int s[MAXN], t[MAXN];
int n, m;

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int dfs(int num, int target) {
    if (num == target)
        return 0;
    char str[20];
    sprintf(str, "%d", num);
    int len = strlen(str);
    int i, j, k, new_num, cnt = INT_MAX;
    for (i = 0; i < len; i++) {
        for (j = i + 1; j < len; j++) {
            new_num = num;
            int d1 = str[i] - '0', d2 = str[j] - '0';
            new_num = new_num / 100 * 100 + d2 * 10 + d1;
            if (new_num != num && new_num <= num)
                cnt = fmin(cnt, 1 + dfs(new_num, target));
        }
    }
    for (i = 0; i < len; i++) {
        new_num = num;
        new_num /= 10;
        if (new_num != num && new_num <= num)
            cnt = fmin(cnt, 1 + dfs(new_num, target));
    }
    for (i = 0; i < len - 1; i++) {
        for (k = 1; k <= 9; k++) {
            if (str[i] < k + '0' && k + '0' < str[i + 1]) {
                new_num = num;
                new_num = new_num / 100 * 100 + k * 10 + str[i] - '0';
                new_num = new_num / 10 * 10 + str[i + 1] - '0';
                if (new_num != num && new_num <= num)
                    cnt = fmin(cnt, 1 + dfs(new_num, target));
            }
        }
    }
    return cnt == INT_MAX ? -1 : cnt;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++)
        scanf("%d", &t[i]);
    int ans[m];
    for (int i = 0; i < m; i++) {
        ans[i] = dfs(n, t[i]);
    }
    for (int i = 0; i < m; i++)
        printf("%d\n", ans[i]);
    return 0;
}