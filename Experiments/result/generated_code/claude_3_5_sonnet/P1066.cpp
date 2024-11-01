#include <stdio.h>
#include <string.h>

#define MAX 60005

int k, w;
char ans[MAX];

void add(char *a, char *b) {
    int len_a = strlen(a), len_b = strlen(b);
    int carry = 0, i;
    for (i = 0; i < len_a || i < len_b || carry; i++) {
        int x = i < len_a ? a[len_a - 1 - i] - '0' : 0;
        int y = i < len_b ? b[len_b - 1 - i] - '0' : 0;
        int sum = x + y + carry;
        if (i < len_a) a[len_a - 1 - i] = sum % 10 + '0';
        else a[i] = sum % 10 + '0';
        carry = sum / 10;
    }
    if (i > len_a) a[i] = '\0';
    for (int j = 0; j < i / 2; j++) {
        char temp = a[j];
        a[j] = a[i - 1 - j];
        a[i - 1 - j] = temp;
    }
}

int main() {
    scanf("%d %d", &k, &w);

    char dp[2][MAX] = {"1"};
    int cur = 0, pre = 1;
    strcpy(ans, "0");

    for (int i = 1; i <= w / k; i++) {
        cur ^= 1;
        pre ^= 1;
        memset(dp[cur], 0, sizeof(dp[cur]));
        
        for (int j = 0; j < (1 << k) - 1; j++) {
            add(dp[cur], dp[pre]);
        }
        
        add(ans, dp[cur]);
    }

    int start = 0;
    while (ans[start] == '0' && ans[start + 1] != '\0') start++;
    printf("%s\n", ans + start);

    return 0;
}