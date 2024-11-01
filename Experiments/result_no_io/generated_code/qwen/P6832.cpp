#include <stdio.h>
#include <string.h>

#define MAXN 10000001

int main() {
    char S[MAXN];
    int n = strlen(fgets(S, sizeof(S), stdin));
    if (n > 0 && S[n-1] == '\n') S[--n] = '\0';

    int cnt[26][MAXN] = {0};
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            cnt[S[j] - 'a'][i]++;
        }
    }

    int max_cnt = 0;
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < n; ++j) {
            max_cnt = (max_cnt > cnt[i][j]) ? max_cnt : cnt[i][j];
        }
    }

    printf("%d\n", max_cnt);
    return 0;
}