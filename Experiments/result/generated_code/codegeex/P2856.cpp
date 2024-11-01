#include <stdio.h>
#include <string.h>

int b, l, d;
char dic[1001][11], cow[27];
int dp[1001];
int ans[1001];

int main() {
    scanf("%d%d%d", &b, &l, &d);
    for (int i = 0; i < d; i++) {
        scanf("%s", dic[i]);
    }

    for (int i = 1; i <= l; i++) {
        memset(dp, 0, sizeof(dp));
        memset(ans, 0, sizeof(ans));
        int max = 0;

        for (int j = i; j <= l; j++) {
            int len = strlen(dic[j - 1]);
            int flag = 1;
            for (int k = 0; k < len; k++) {
                if (dic[j - 1][k] - 'A' < i - 1 || dic[j - 1][k] - 'A' >= j) {
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                for (int k = 0; k < len; k++) {
                    int c = dic[j - 1][k] - 'A' - (i - 1);
                    ans[c]++;
                }
            }
            for (int k = 0; k < i; k++) {
                int sum = 0;
                for (int h = 0; h < b; h++) {
                    sum += ans[h];
                }
                dp[i] = sum;
                if (dp[i] > max) {
                    max = dp[i];
                    cow[i] = j + 'A' - 1;
                }
                ans[0]++;
                for (int h = 1; h < b; h++) {
                    ans[h] = ans[h - 1];
                }
            }
        }

        for (int j = 0; j < b; j++) {
            printf("%c", cow[j]);
        }
        printf("\n");
    }

    return 0;
}