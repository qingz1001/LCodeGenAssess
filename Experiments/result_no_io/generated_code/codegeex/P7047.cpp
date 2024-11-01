#include <stdio.h>
#include <string.h>

char str[1501];
__int128 sum[1501];
__int128 min_var = (__int128)1 << 63;
__int128 results[1501];

void dfs(int pos, int n) {
    if (pos == n) {
        __int128 var = 0;
        __int128 avg = (sum[n] + sum[n - 1]) / 2;
        for (int i = 0; i < n; i++) {
            var += (sum[i + 1] - avg) * (sum[i + 1] - avg);
        }
        if (var < min_var) {
            min_var = var;
            memset(results, 0, sizeof(results));
            for (int i = 0; i < n; i++) {
                results[i] = sum[i + 1] - sum[i];
            }
        } else if (var == min_var) {
            __int128 value = 0;
            for (int i = 0; i < n; i++) {
                value = (value << 1) | (str[i] - '0');
            }
            int j = 0;
            while (j < n && value > results[j]) j++;
            for (int i = n; i > j; i--) {
                results[i] = results[i - 1];
            }
            results[j] = value;
        }
        return;
    }
    str[pos] = '0';
    sum[pos + 1] = sum[pos] + (pos + 1);
    dfs(pos + 1, n);
    str[pos] = '1';
    sum[pos + 1] = sum[pos] + (pos + 1);
    dfs(pos + 1, n);
}

int main() {
    int n;
    scanf("%s", str);
    n = strlen(str);
    dfs(0, n);
    for (int i = 0; i < n; i++) {
        printf("%c", results[i] & 1 ? '1' : '0');
    }
    printf("\n");
    return 0;
}